#include "root-restart-traversal-behavior.hpp"

Transduction::RootRestartTraversalBehavior::RootRestartTraversalBehavior(
  Transduction::SyntaxTreeIteratorStrategy* iteratorFactory
) : Transduction::TraversalBehavior(iteratorFactory) {}

void Transduction::RootRestartTraversalBehavior::start(SyntaxTree* tree)
{
  this->root = tree;
  TraversalBehavior::start(tree);
}

Transduction::SyntaxTree* 
Transduction::RootRestartTraversalBehavior::next()
{
  SyntaxTree& result = *current;
  ++current;
  return &result;
}

void Transduction::RootRestartTraversalBehavior::notifyTransduction()
{
  current = this->createIterator(this->root);
}