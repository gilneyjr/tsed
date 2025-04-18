#ifndef RESTART_FROM_ROOT_TRANSVERSAL_STRATEGY_HPP
#define RESTART_FROM_ROOT_TRANSVERSAL_STRATEGY_HPP

#include "transversal-strategy.hpp"

namespace Transduction
{
  class RestartFromRootTransversalStrategy : public TransversalStrategy
  {
  protected:
    SyntaxTree* root;
  public:
    RestartFromRootTransversalStrategy(SyntaxTreeIteratorStrategy*);
    void start(SyntaxTree*) override;
    SyntaxTree* next() override;
    void notifyTransduction() override;
  };
}

#endif
