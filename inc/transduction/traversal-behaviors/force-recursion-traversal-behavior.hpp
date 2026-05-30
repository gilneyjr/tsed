#ifndef FORCE_RECURSION_TRAVERSAL_BEHAVIOR_HPP
#define FORCE_RECURSION_TRAVERSAL_BEHAVIOR_HPP

#include "traversal-behavior.hpp"
#include <set>

namespace Transduction
{
  class ForceRecursionTraversalBehavior : public TraversalBehavior    
  {
  private:
    bool nextIsMainPlaceholder;
    static std::set<SyntaxTree*> getCutMatchedSubtrees(const SymbolTable &symbolTable);
    SyntaxTree* getTopmostCutSubtreeInAncestry(const std::set<SyntaxTree*> &cutMatchedSubtrees);
    void advanceNextPastSubtree(SyntaxTree *subtree);
  public:
    ForceRecursionTraversalBehavior(SyntaxTreeIteratorStrategy *iteratorStrategy);
    void notifyMatch(const SymbolTable &symbolTable) override;
    void notifyReplacement(const std::vector<SyntaxTree*> &replacedTrees) override;
  };
}

#endif
