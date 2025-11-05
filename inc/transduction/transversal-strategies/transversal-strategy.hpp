#ifndef TRANSVERSAL_STRATEGY_HPP
#define TRANSVERSAL_STRATEGY_HPP

#include "syntax-tree.hpp"
#include "syntax-tree-iterator.hpp"
#include "syntax-tree-iterator-strategy.hpp"

namespace Transduction
{
  class TransversalStrategy
  {
  protected:
    SyntaxTreeIteratorStrategy* iteratorStrategy;
    SyntaxTreeIterator current;
    SyntaxTreeIterator createIterator(SyntaxTree*);
  public:
    TransversalStrategy(SyntaxTreeIteratorStrategy*);
    virtual ~TransversalStrategy();
    virtual void start(SyntaxTree*);
    bool hasNext();
    virtual SyntaxTree* next() = 0;
    virtual void notifyTransduction() = 0; // TODO: review parameters when implement other transversals
  };
}

#endif
