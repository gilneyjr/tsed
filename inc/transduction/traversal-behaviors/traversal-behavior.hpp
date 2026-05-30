#ifndef TRAVERSAL_BEHAVIOR_HPP
#define TRAVERSAL_BEHAVIOR_HPP

#include "symbol-table.hpp"
#include "syntax-tree.hpp"
#include "syntax-tree-iterator.hpp"
#include "syntax-tree-iterator-strategy.hpp"

namespace Transduction
{
  class TraversalBehavior
  {
  protected:
    SyntaxTreeIteratorStrategy* iteratorStrategy;
    SyntaxTreeIterator _next;
    SyntaxTreeIterator createIterator(SyntaxTree *tree);
  public:
    TraversalBehavior(SyntaxTreeIteratorStrategy *iteratorStrategy);
    virtual ~TraversalBehavior();
    virtual void start(SyntaxTree *tree);
    bool hasNext();
    virtual SyntaxTree* next();
    virtual void notifyMatch(const Transduction::SymbolTable &symbolTable) = 0;
    virtual void notifyReplacement(const std::vector<SyntaxTree*> &replacedTrees) = 0;
  };
}

#endif
