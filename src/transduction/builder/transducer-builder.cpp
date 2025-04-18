#include <stdexcept>
#include "post-order-syntax-tree-iterator-strategy.hpp"
#include "pre-order-syntax-tree-iterator-strategy.hpp"
#include "restart-from-root-transversal-strategy.hpp"
#include "stop-transversal-strategy.hpp"
#include "transducer-builder.hpp"

Transduction::TransducerBuilder::TransducerBuilder()
{
  this->iteratorType = SyntaxTreeIteratorStrategyType::PRE_ORDER;
  this->transversalType = TransversalStrategyType::STOP; // TODO: change this later
}

Transduction::TransducerBuilder& 
Transduction::TransducerBuilder::setIteratorStrategyType(SyntaxTreeIteratorStrategyType type)
{
  this->iteratorType = type;
  return *this;
}

Transduction::TransducerBuilder& 
Transduction::TransducerBuilder::setTransversalStrategyType(TransversalStrategyType type)
{
  this->transversalType = type;
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

  TransversalStrategy* transversalStrategy = nullptr;
  switch (transversalType)
  {
    case TransversalStrategyType::RESTART_FROM_ROOT:
      transversalStrategy = new RestartFromRootTransversalStrategy(iteratorStrategy);
      break;
    case TransversalStrategyType::STOP:
      transversalStrategy = new StopTransversalStrategy(iteratorStrategy);
      break;
  }

  return new Transducer(transversalStrategy);
}