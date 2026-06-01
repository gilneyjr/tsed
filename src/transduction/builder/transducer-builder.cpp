#include <stdexcept>
#include "follow-replacement-traversal-behavior.hpp"
#include "force-recursion-traversal-behavior.hpp"
#include "post-order-syntax-tree-iterator-strategy.hpp"
#include "pre-order-syntax-tree-iterator-strategy.hpp"
#include "root-restart-traversal-behavior.hpp"
#include "single-match-traversal-behavior.hpp"
#include "skip-modified-traversal-behavior.hpp"
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
    case TraversalBehaviorType::FOLLOW_REPLACEMENT:
      traversalBehavior = new FollowReplacementTraversalBehavior(iteratorStrategy);
      break;
    case TraversalBehaviorType::SKIP_MODIFIED:
      traversalBehavior = new SkipModifiedTraversalBehavior(iteratorStrategy);
      break;
    case TraversalBehaviorType::FORCE_RECURSION:
      traversalBehavior = new ForceRecursionTraversalBehavior(iteratorStrategy);
      break;
    case TraversalBehaviorType::SINGLE_MATCH:
      traversalBehavior = new SingleMatchTraversalBehavior(iteratorStrategy);
      break;
    case TraversalBehaviorType::ROOT_RESTART:
      traversalBehavior = new RootRestartTraversalBehavior(iteratorStrategy);
      break;
  }

  return new Transducer(traversalBehavior);
}