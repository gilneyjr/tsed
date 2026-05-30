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
    SingleMatchTraversalBehavior(SyntaxTreeIteratorStrategy *iteratorStrategy);
    void notifyMatch(const Transduction::SymbolTable &symbolTable) override;
    void notifyReplacement(const std::vector<SyntaxTree*> &replacedTrees) override;
  };
}

#endif
