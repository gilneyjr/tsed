#include "transversal-strategy.hpp"

Transduction::TransversalStrategy::TransversalStrategy(
  Transduction::SyntaxTreeIteratorStrategy* iteratorStrategy
): iteratorStrategy(iteratorStrategy) {}

Transduction::TransversalStrategy::~TransversalStrategy()
{
  if (this->iteratorStrategy)
    delete this->iteratorStrategy;
}

void Transduction::TransversalStrategy::start(Transduction::SyntaxTree *tree)
{
  this->current = this->createIterator(tree);
}

bool Transduction::TransversalStrategy::hasNext()
{
  return this->current != this->createIterator(nullptr);
}

Transduction::SyntaxTreeIterator
Transduction::TransversalStrategy::createIterator(Transduction::SyntaxTree *tree)
{
  return SyntaxTreeIterator(tree, this->iteratorStrategy);
}