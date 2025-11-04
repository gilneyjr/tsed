#ifndef IS_LEFTMOST_DESCENDANT_OF_EXPRESSION_HPP
#define IS_LEFTMOST_DESCENDANT_OF_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class IsLeftmostDescendantOfExpression : public SearchExpression
  {
  private:
    SearchExpression* expression;
  public:
    IsLeftmostDescendantOfExpression(SearchExpression*);
    ~IsLeftmostDescendantOfExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
