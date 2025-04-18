#include "restart-from-root-transversal-strategy.hpp"

Transduction::RestartFromRootTransversalStrategy::RestartFromRootTransversalStrategy(
  Transduction::SyntaxTreeIteratorStrategy* iteratorFactory
) : Transduction::TransversalStrategy(iteratorFactory) {}

void Transduction::RestartFromRootTransversalStrategy::start(SyntaxTree* tree)
{
  this->root = tree;
  TransversalStrategy::start(tree);
}

Transduction::SyntaxTree* 
Transduction::RestartFromRootTransversalStrategy::next()
{
  SyntaxTree& result = *current;
  ++current;
  return &result;
}

void Transduction::RestartFromRootTransversalStrategy::notifyTransduction()
{
  current = this->createIterator(this->root);
}