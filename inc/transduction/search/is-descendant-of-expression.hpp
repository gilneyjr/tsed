#ifndef IS_DESCENDANT_OF_EXPRESSION_HPP
#define IS_DESCENDANT_OF_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class IsDescendantOfExpression : public SearchExpression
  {
  private:
    SearchExpression* expression;
  public:
    IsDescendantOfExpression(SearchExpression*);
    ~IsDescendantOfExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
