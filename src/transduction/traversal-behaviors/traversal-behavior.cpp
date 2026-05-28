#include "traversal-behavior.hpp"

Transduction::TraversalBehavior::TraversalBehavior(
  Transduction::SyntaxTreeIteratorStrategy* iteratorStrategy
): iteratorStrategy(iteratorStrategy) {}

Transduction::TraversalBehavior::~TraversalBehavior()
{
  if (this->iteratorStrategy)
    delete this->iteratorStrategy;
}

void Transduction::TraversalBehavior::start(Transduction::SyntaxTree *tree)
{
  this->current = this->createIterator(tree);
}

bool Transduction::TraversalBehavior::hasNext()
{
  return this->current != this->createIterator(nullptr);
}

Transduction::SyntaxTreeIterator
Transduction::TraversalBehavior::createIterator(Transduction::SyntaxTree *tree)
{
  return SyntaxTreeIterator(tree, this->iteratorStrategy);
}