#include "traversal-behavior.hpp"

Transduction::TraversalBehavior::TraversalBehavior(
  Transduction::SyntaxTreeIteratorStrategy* iteratorStrategy
): iteratorStrategy(iteratorStrategy)
{
  _current = createIterator(nullptr);
  _next = createIterator(nullptr);
}

Transduction::TraversalBehavior::~TraversalBehavior()
{
  if (this->iteratorStrategy)
    delete this->iteratorStrategy;
}

std::set<Transduction::SyntaxTree*>
Transduction::TraversalBehavior::getCutMatchedSubtrees(
  const SymbolTable &symbolTable)
{
  std::set<SyntaxTree*> subtrees;
  for (const auto &[_, match] : symbolTable.getAllMatches())
    if (match.placeholder == Nodename::Placeholder::CUT)
      subtrees.insert(match.trees.cbegin(), match.trees.cend());
  return subtrees;
}

Transduction::SyntaxTree*
Transduction::TraversalBehavior::getTopmostCutSubtreeInAncestry(
  const std::set<SyntaxTree*> &cutPlaceholderSubtrees)
{
  SyntaxTree *topmostCutSubtreeInAncestry = nullptr;

  auto subtree = &*_next;
  if (subtree->isEndMarker())
  {
    if (subtree->getParent() != nullptr)
      subtree = subtree->getParent();
    else if (subtree->getLeftSibling() != nullptr)
      subtree = subtree->getLeftSibling();
    else if (subtree->getRightSibling() != nullptr)
      subtree = subtree->getRightSibling();
  }

  while (subtree != nullptr && !subtree->isEndMarker())
  {
    if (cutPlaceholderSubtrees.find(subtree) != cutPlaceholderSubtrees.end())
      topmostCutSubtreeInAncestry = subtree;
    subtree = subtree->getParent();
  }

  return topmostCutSubtreeInAncestry;
}

void Transduction::TraversalBehavior::advanceNextPastSubtree(SyntaxTree *subtree)
{
  _next = createIterator(subtree);
  while (hasNext())
  {
    if (!(&*_next)->isInSubtree(subtree))
      break;
    ++_next;
  }
}

void Transduction::TraversalBehavior::start(Transduction::SyntaxTree *tree)
{
  this->_next = this->createIterator(tree);
  this->_current = this->createIterator(nullptr);
}

bool Transduction::TraversalBehavior::hasNext()
{
  return this->_next != this->createIterator(nullptr);
}

Transduction::SyntaxTree* 
Transduction::TraversalBehavior::next()
{
  SyntaxTree *result = &*_next;
  _current = createIterator(result);
  ++_next;
  return result;
}

Transduction::SyntaxTreeIterator
Transduction::TraversalBehavior::createIterator(Transduction::SyntaxTree *tree)
{
  return SyntaxTreeIterator(tree, this->iteratorStrategy);
}