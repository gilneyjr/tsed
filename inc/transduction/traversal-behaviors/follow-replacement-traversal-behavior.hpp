#ifndef FOLLOW_REPLACEMENT_TRAVERSAL_BEHAVIOR_HPP
#define FOLLOW_REPLACEMENT_TRAVERSAL_BEHAVIOR_HPP

#include "traversal-behavior.hpp"

namespace Transduction
{
  class FollowReplacementTraversalBehavior : public TraversalBehavior
  {
  public:
    FollowReplacementTraversalBehavior(SyntaxTreeIteratorStrategy *iteratorStrategy);
    void notifyMatch(const SymbolTable &symbolTable) override;
    void notifyReplacement(const std::vector<SyntaxTree*> &replacedTrees) override;
  };
}

#endif
