#include "single-match-traversal-behavior.hpp"
#include <iostream>

Transduction::SingleMatchTraversalBehavior::SingleMatchTraversalBehavior(
  Transduction::SyntaxTreeIteratorStrategy* iteratorFactory
) : Transduction::TraversalBehavior(iteratorFactory) {}

Transduction::SyntaxTree* 
Transduction::SingleMatchTraversalBehavior::next()
{
  SyntaxTree& result = *current;
  ++current;
  return &result;
}

void Transduction::SingleMatchTraversalBehavior::notifyTransduction()
{
  current = this->createIterator(nullptr);
}