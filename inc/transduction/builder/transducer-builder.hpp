#ifndef TRANSDUCER_BUILDER_HPP
#define TRANSDUCER_BUILDER_HPP

#include "syntax-tree-iterator-strategy-type.hpp"
#include "transducer.hpp"
#include "transversal-strategy-type.hpp"

namespace Transduction
{
  class TransducerBuilder
  {
  protected:
    SyntaxTreeIteratorStrategyType iteratorType;
    TransversalStrategyType transversalType;
  public:
    TransducerBuilder();
    TransducerBuilder& setIteratorStrategyType(SyntaxTreeIteratorStrategyType);
    TransducerBuilder& setTransversalStrategyType(TransversalStrategyType);
    Transducer* build();
  };
}

#endif
