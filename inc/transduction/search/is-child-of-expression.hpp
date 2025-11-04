#ifndef IS_CHILD_OF_EXPRESSION_HPP
#define IS_CHILD_OF_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class IsChildOfExpression : public SearchExpression
  {
  private:
    SearchExpression* expression;
  public:
    IsChildOfExpression(SearchExpression*);
    ~IsChildOfExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
