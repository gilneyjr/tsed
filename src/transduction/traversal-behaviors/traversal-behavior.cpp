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