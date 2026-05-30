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
    RootRestartTraversalBehavior(SyntaxTreeIteratorStrategy *iteratorStrategy);
    void start(SyntaxTree *tree) override;
    void notifyMatch(const Transduction::SymbolTable &symbolTable) override;
    void notifyReplacement(const std::vector<SyntaxTree*> &replacedTrees) override;
  };
}

#endif
