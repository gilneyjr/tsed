#ifndef IS_EQUAL_TO_EXPRESSION_HPP
#define IS_EQUAL_TO_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class IsEqualToExpression : public SearchExpression
  {
  private:
    SearchExpression* expression;
  public:
    IsEqualToExpression(SearchExpression*);
    ~IsEqualToExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
