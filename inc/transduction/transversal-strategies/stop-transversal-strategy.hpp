#ifndef STOP_TRANSVERSAL_STRATEGY_HPP
#define STOP_TRANSVERSAL_STRATEGY_HPP

#include "transversal-strategy.hpp"

namespace Transduction
{
  class StopTransversalStrategy : public TransversalStrategy
  {
  protected:
    SyntaxTree* root;
  public:
    StopTransversalStrategy(SyntaxTreeIteratorStrategy*);
    SyntaxTree* next() override;
    void notifyTransduction() override;
  };
}

#endif
