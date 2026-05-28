#ifndef TRANSDUCER_BUILDER_HPP
#define TRANSDUCER_BUILDER_HPP

#include "syntax-tree-iterator-strategy-type.hpp"
#include "transducer.hpp"
#include "traversal-behavior-type.hpp"

namespace Transduction
{
  class TransducerBuilder
  {
  protected:
    SyntaxTreeIteratorStrategyType iteratorType;
    TraversalBehaviorType traversalType;
  public:
    TransducerBuilder();
    TransducerBuilder& setIteratorStrategyType(SyntaxTreeIteratorStrategyType);
    TransducerBuilder& setTraversalBehaviorType(TraversalBehaviorType);
    Transducer* build();
  };
}

#endif
