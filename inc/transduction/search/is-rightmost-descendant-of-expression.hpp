#ifndef IS_RIGHTMOST_DESCENDANT_OF_EXPRESSION_HPP
#define IS_RIGHTMOST_DESCENDANT_OF_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class IsRightmostDescendantOfExpression : public SearchExpression
  {
  private:
    SearchExpression* expression;
  public:
    IsRightmostDescendantOfExpression(SearchExpression*);
    ~IsRightmostDescendantOfExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
