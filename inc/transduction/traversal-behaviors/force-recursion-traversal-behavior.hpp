#ifndef FORCE_RECURSION_TRAVERSAL_BEHAVIOR_HPP
#define FORCE_RECURSION_TRAVERSAL_BEHAVIOR_HPP

#include "traversal-behavior.hpp"

namespace Transduction
{
  class ForceRecursionTraversalBehavior : public TraversalBehavior
  {
  private:
    bool nextIsMainPlaceholder;
    bool advanceReplacementRoot;
    bool currentIsInMainPlaceholder;
  public:
    ForceRecursionTraversalBehavior(
      SyntaxTreeIteratorStrategy *iteratorStrategy,
      bool advanceReplacementRoot = false
    );
    void notifyMatch(const SymbolTable &symbolTable) override;
    void notifyReplacement(const std::vector<SyntaxTree*> &replacedTrees) override;
  };
}

#endif
