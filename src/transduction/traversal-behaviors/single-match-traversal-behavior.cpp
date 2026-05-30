#include "single-match-traversal-behavior.hpp"
#include <iostream>

Transduction::SingleMatchTraversalBehavior::SingleMatchTraversalBehavior(
  Transduction::SyntaxTreeIteratorStrategy* iteratorFactory
) : Transduction::TraversalBehavior(iteratorFactory) {}

void Transduction::SingleMatchTraversalBehavior::notifyMatch(const Transduction::SymbolTable&)
{
  _next = this->createIterator(nullptr);
}

void Transduction::SingleMatchTraversalBehavior::notifyReplacement(const std::vector<SyntaxTree*>&)
{
  // No action required here
}