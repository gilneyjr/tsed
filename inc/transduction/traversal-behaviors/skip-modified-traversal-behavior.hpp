#ifndef SKIP_MODIFIED_TRAVERSAL_BEHAVIOR_HPP
#define SKIP_MODIFIED_TRAVERSAL_BEHAVIOR_HPP

#include "traversal-behavior.hpp"

#include <set>

namespace Transduction
{
  class SkipModifiedTraversalBehavior : public TraversalBehavior
  {
  private:
    std::set<SyntaxTree*> modified;
  public:
    SkipModifiedTraversalBehavior(SyntaxTreeIteratorStrategy *iteratorStrategy);
    void start(SyntaxTree *tree) override;
    void notifyMatch(const SymbolTable &symbolTable) override;
    void notifyReplacement(const std::vector<SyntaxTree*> &replacedTrees) override;
  };
}

#endif

