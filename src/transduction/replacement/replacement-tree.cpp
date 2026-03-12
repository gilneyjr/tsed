#include "replacement-tree.hpp"

Transduction::Replacement::ReplacementTree::ReplacementTree(
  const std::string &tag,
  Nodename::Placeholder placeholder,
  unsigned int placeholderNumber
) : tag(tag), placeholder(placeholder), placeholderNumber(placeholderNumber)
{
  children = new TreeSequence;
}

Transduction::Replacement::ReplacementTree::ReplacementTree(
  const std::string &tag,
  TreeSequence *children
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

const Transduction::Replacement::TreeSequence* Transduction::Replacement::ReplacementTree::getChildren() const
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

void Transduction::Replacement::ReplacementTree::setChildren(Transduction::Replacement::TreeSequence *children)
{
  if (this->children != nullptr)
    delete this->children;
  this->children = children;
}
