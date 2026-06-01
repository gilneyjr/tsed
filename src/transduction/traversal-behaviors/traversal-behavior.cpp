#include "traversal-behavior.hpp"

Transduction::TraversalBehavior::TraversalBehavior(
  Transduction::SyntaxTreeIteratorStrategy* iteratorStrategy
): iteratorStrategy(iteratorStrategy) {}

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
  for (auto subtree = &*_next; subtree != nullptr && !subtree->isEndMarker(); subtree = subtree->getParent())
  {
    if (cutPlaceholderSubtrees.find(subtree) != cutPlaceholderSubtrees.end())
      topmostCutSubtreeInAncestry = subtree;
  }
  return topmostCutSubtreeInAncestry;
}

void Transduction::TraversalBehavior::advanceNextPastSubtree(SyntaxTree *subtree)
{
  _next = createIterator(subtree);

  while (hasNext())
  {
    bool isInsideSubtree = false;
    for (SyntaxTree* node = &*_next; node != nullptr; node = node->getParent())
    {
      if (node == subtree)
      {
        isInsideSubtree = true;
        break;
      }
    }

    if (!isInsideSubtree)
      break;
    ++_next;
  }
}

void Transduction::TraversalBehavior::start(Transduction::SyntaxTree *tree)
{
  this->_next = this->createIterator(tree);
}

bool Transduction::TraversalBehavior::hasNext()
{
  return this->_next != this->createIterator(nullptr);
}

Transduction::SyntaxTree* 
Transduction::TraversalBehavior::next()
{
  SyntaxTree& result = *_next;
  ++_next;
  return &result;
}

Transduction::SyntaxTreeIterator
Transduction::TraversalBehavior::createIterator(Transduction::SyntaxTree *tree)
{
  return SyntaxTreeIterator(tree, this->iteratorStrategy);
}