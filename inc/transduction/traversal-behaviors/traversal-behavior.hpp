#ifndef TRAVERSAL_BEHAVIOR_HPP
#define TRAVERSAL_BEHAVIOR_HPP

#include "syntax-tree.hpp"
#include "syntax-tree-iterator.hpp"
#include "syntax-tree-iterator-strategy.hpp"

namespace Transduction
{
  class TraversalBehavior
  {
  protected:
    SyntaxTreeIteratorStrategy* iteratorStrategy;
    SyntaxTreeIterator current;
    SyntaxTreeIterator createIterator(SyntaxTree*);
  public:
    TraversalBehavior(SyntaxTreeIteratorStrategy*);
    virtual ~TraversalBehavior();
    virtual void start(SyntaxTree*);
    bool hasNext();
    virtual SyntaxTree* next() = 0;
    virtual void notifyTransduction() = 0; // TODO: review parameters when implement other traversals
  };
}

#endif
