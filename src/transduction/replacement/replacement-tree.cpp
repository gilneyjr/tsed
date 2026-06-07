#include "replacement-tree.hpp"
#include "replacement-tree-sequence.hpp"

Transduction::Replacement::ReplacementTree::ReplacementTree(
  const std::string &tag,
  Nodename::Placeholder placeholder,
  unsigned int placeholderNumber
) : tag(tag), placeholder(placeholder), placeholderNumber(placeholderNumber)
{
  children = new ReplacementTreeSequence;
}

Transduction::Replacement::ReplacementTree::ReplacementTree(
  const std::string &tag,
  ReplacementTreeSequence *children
) : tag(tag), children(children)
{
  placeholder = Nodename::Placeholder::NONE;
  placeholderNumber = 0;
}

Transduction::Replacement::ReplacementTree::~ReplacementTree()
{
  delete children;
}

const std::string &Transduction::Replacement::ReplacementTree::getTag() const
{
  return tag;
}

Nodename::Placeholder Transduction::Replacement::ReplacementTree::getPlaceholder() const
{
  return placeholder;
}

unsigned int Transduction::Replacement::ReplacementTree::getPlaceholderNumber() const
{
  return placeholderNumber;
}

const Transduction::Replacement::ReplacementTreeSequence*
Transduction::Replacement::ReplacementTree::getChildren() const
{
  return children;
}

void Transduction::Replacement::ReplacementTree::validate(Contexts::ReplacementValidationContext &context) const
{
  // leaf node
  if (children->empty())
  {
    if (placeholder == Nodename::Placeholder::NONE)
      return;

    auto definitionIt = context.searchDefinitions.find(placeholderNumber);
    if (definitionIt == context.searchDefinitions.end())
      // TODO: Correct/improve this message error
      context.errors.emplace_back("Reference to placeholder is not defined in search expression.");
    else if (definitionIt->second->placeholder != placeholder)
      // TODO: Correct/improve this message error
      context.errors.emplace_back("Reference has different placeholder type from definition.");

    return;
  }

  // internal node
  if (placeholder != Nodename::Placeholder::NONE)
    // TODO: Correct/improve this message error
    context.errors.emplace_back("Tree roots in replacement expression cannot have a placeholder.");

  for (auto child : *children)
    child->validate(context);
}

std::vector<Transduction::SyntaxTree*>
Transduction::Replacement::ReplacementTree::generateSyntaxTrees(
  const std::map<unsigned int, Transduction::NodenameMatch> &matches) const
{
  if (placeholder != Nodename::Placeholder::NONE)
  {
    const Transduction::NodenameMatch &match = matches.at(placeholderNumber);

    if (match.isRange)
    {
      // TODO: Add validation for if match is range, it cannot have a tag
      std::vector<Transduction::SyntaxTree*> generatedTrees;
      for (SyntaxTree* tree : match.trees)
        generatedTrees.push_back(tree->clone());
      return generatedTrees;
    }
    else
    {
      std::string newTag = match.left + tag + match.right;
      SyntaxTree* generatedTree = match.trees.front()->clone();
      if (!tag.empty())
        generatedTree->setTag(newTag);
      return std::vector<SyntaxTree*>({ generatedTree });
    }
  }

  SyntaxTree *tree = new SyntaxTree(tag);

  if (children != nullptr)
  {
    auto generatedChildren = children->generateSyntaxTrees(matches);
    for (SyntaxTree* child : generatedChildren)
      tree->addChild(child);
  }

  return std::vector<SyntaxTree*>({ tree });
}

void Transduction::Replacement::ReplacementTree::setChildren(
  Transduction::Replacement::ReplacementTreeSequence *children)
{
  if (this->children != nullptr)
    delete this->children;
  this->children = children;
}
