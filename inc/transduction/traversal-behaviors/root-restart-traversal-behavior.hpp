#ifndef ROOT_RESTART_TRAVERSAL_BEHAVIOR_HPP
#define ROOT_RESTART_TRAVERSAL_BEHAVIOR_HPP

#include "traversal-behavior.hpp"

namespace Transduction
{
  class RootRestartTraversalBehavior : public TraversalBehavior
  {
  protected:
    SyntaxTree* root;
  public:
    RootRestartTraversalBehavior(SyntaxTreeIteratorStrategy*);
    void start(SyntaxTree*) override;
    SyntaxTree* next() override;
    void notifyTransduction() override;
  };
}

#endif
