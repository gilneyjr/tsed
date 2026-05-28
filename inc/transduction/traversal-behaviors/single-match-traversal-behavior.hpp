#ifndef SINGLE_MATCH_TRAVERSAL_BEHAVIOR_HPP
#define SINGLE_MATCH_TRAVERSAL_BEHAVIOR_HPP

#include "traversal-behavior.hpp"

namespace Transduction
{
  class SingleMatchTraversalBehavior : public TraversalBehavior
  {
  protected:
    SyntaxTree* root;
  public:
    SingleMatchTraversalBehavior(SyntaxTreeIteratorStrategy*);
    SyntaxTree* next() override;
    void notifyTransduction() override;
  };
}

#endif
