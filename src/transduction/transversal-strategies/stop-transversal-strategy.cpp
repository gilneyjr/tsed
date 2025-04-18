#include "stop-transversal-strategy.hpp"
#include <iostream> // TODO: remove it later

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
  std::cout << "MATCHED: StopTransversalStrategy" << std::endl; 
  current = this->createIterator(nullptr);
}