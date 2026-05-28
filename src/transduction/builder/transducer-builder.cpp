#include <stdexcept>
#include "post-order-syntax-tree-iterator-strategy.hpp"
#include "pre-order-syntax-tree-iterator-strategy.hpp"
#include "root-restart-traversal-behavior.hpp"
#include "single-match-traversal-behavior.hpp"
#include "transducer-builder.hpp"

Transduction::TransducerBuilder::TransducerBuilder()
{
  this->iteratorType = SyntaxTreeIteratorStrategyType::PRE_ORDER;
  this->traversalType = TraversalBehaviorType::SINGLE_MATCH; // TODO: change this later
}

Transduction::TransducerBuilder& 
Transduction::TransducerBuilder::setIteratorStrategyType(SyntaxTreeIteratorStrategyType type)
{
  this->iteratorType = type;
  return *this;
}

Transduction::TransducerBuilder& 
Transduction::TransducerBuilder::setTraversalBehaviorType(TraversalBehaviorType type)
{
  this->traversalType = type;
  return *this;
}

Transduction::Transducer*
Transduction::TransducerBuilder::build()
{
  SyntaxTreeIteratorStrategy* iteratorStrategy = nullptr;
  switch (iteratorType)
  {
    case SyntaxTreeIteratorStrategyType::PRE_ORDER:
      iteratorStrategy = new PreOrderSyntaxTreeIteratorStrategy();
      break;
    case SyntaxTreeIteratorStrategyType::POST_ORDER:
      iteratorStrategy = new PostOrderSyntaxTreeIteratorStrategy();
      break;
  }

  TraversalBehavior* traversalBehavior = nullptr;
  switch (traversalType)
  {
    case TraversalBehaviorType::ROOT_RESTART:
      traversalBehavior = new RootRestartTraversalBehavior(iteratorStrategy);
      break;
    case TraversalBehaviorType::SINGLE_MATCH:
      traversalBehavior = new SingleMatchTraversalBehavior(iteratorStrategy);
      break;
  }

  return new Transducer(traversalBehavior);
}