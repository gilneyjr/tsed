#ifndef PRE_ORDER_SYNTAX_TREE_ITERATOR_STRATEGY_HPP
#define PRE_ORDER_SYNTAX_TREE_ITERATOR_STRATEGY_HPP

#include "syntax-tree-iterator-strategy.hpp"

namespace Transduction
{
  class PreOrderSyntaxTreeIteratorStrategy : public SyntaxTreeIteratorStrategy 
  {
  public:
    SyntaxTree* start(SyntaxTree*) override;
    SyntaxTree* next(SyntaxTree*) override;
    IteratorDirection direction() override;
  }; 
}

#endif
