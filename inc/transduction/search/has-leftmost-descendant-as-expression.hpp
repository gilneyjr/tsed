#ifndef HAS_LEFTMOST_DESCENDANT_AS_EXPRESSION_HPP
#define HAS_LEFTMOST_DESCENDANT_AS_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class HasLeftmostDescendantAsExpression : public SearchExpression
  {
  private:
    SearchExpression* expression;
  public:
    HasLeftmostDescendantAsExpression(SearchExpression*);
    ~HasLeftmostDescendantAsExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
