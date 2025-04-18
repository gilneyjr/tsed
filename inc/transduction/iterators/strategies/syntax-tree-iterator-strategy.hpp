#ifndef SYNTAX_TREE_ITERATOR_STRATEGY_HPP
#define SYNTAX_TREE_ITERATOR_STRATEGY_HPP

#include "syntax-tree.hpp"

namespace Transduction
{
  class SyntaxTreeIteratorStrategy
  {
  public:
    virtual ~SyntaxTreeIteratorStrategy() = default;
    virtual SyntaxTree* start(SyntaxTree*) = 0;
    virtual SyntaxTree* next(SyntaxTree*) = 0;
  }; 
}

#endif
