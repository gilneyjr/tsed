#ifndef IS_UNIQUE_CHILD_OF_EXPRESSION_HPP
#define IS_UNIQUE_CHILD_OF_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class IsUniqueChildOfExpression : public SearchExpression
  {
  private:
    SearchExpression* expression;
  public:
    IsUniqueChildOfExpression(SearchExpression*);
    ~IsUniqueChildOfExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
