#ifndef POST_ORDER_SYNTAX_TREE_ITERATOR_STRATEGY_HPP
#define POST_ORDER_SYNTAX_TREE_ITERATOR_STRATEGY_HPP

#include "syntax-tree-iterator-strategy.hpp"

namespace Transduction
{
  class PostOrderSyntaxTreeIteratorStrategy : public SyntaxTreeIteratorStrategy 
  {
  public:
    SyntaxTree* start(SyntaxTree*) override;
    SyntaxTree* next(SyntaxTree*) override;
  }; 
}

#endif
