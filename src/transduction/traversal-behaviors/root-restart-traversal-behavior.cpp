#include "root-restart-traversal-behavior.hpp"

Transduction::RootRestartTraversalBehavior::RootRestartTraversalBehavior(
  Transduction::SyntaxTreeIteratorStrategy* iteratorFactory
) : Transduction::TraversalBehavior(iteratorFactory) {}

void Transduction::RootRestartTraversalBehavior::start(SyntaxTree* tree)
{
  root = tree;
  TraversalBehavior::start(tree);
}

void Transduction::RootRestartTraversalBehavior::notifyMatch(const Transduction::SymbolTable&)
{
  _next = createIterator(root);
}

void Transduction::RootRestartTraversalBehavior::notifyReplacement(const std::vector<SyntaxTree*>&)
{
  // No action required for this
}