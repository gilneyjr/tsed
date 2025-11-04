#ifndef HAS_RIGHTMOST_DESCENDANT_AS_EXPRESSION_HPP
#define HAS_RIGHTMOST_DESCENDANT_AS_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class HasRightmostDescendantAsExpression : public SearchExpression
  {
  private:
    SearchExpression* expression;
  public:
    HasRightmostDescendantAsExpression(SearchExpression*);
    ~HasRightmostDescendantAsExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
