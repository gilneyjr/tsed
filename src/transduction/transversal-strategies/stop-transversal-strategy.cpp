#include "stop-transversal-strategy.hpp"
#include <iostream>

Transduction::StopTransversalStrategy::StopTransversalStrategy(
  Transduction::SyntaxTreeIteratorStrategy* iteratorFactory
) : Transduction::TransversalStrategy(iteratorFactory) {}

Transduction::SyntaxTree* 
Transduction::StopTransversalStrategy::next()
{
  SyntaxTree& result = *current;
  ++current;
  return &result;
}

void Transduction::StopTransversalStrategy::notifyTransduction()
{
  current = this->createIterator(nullptr);
}