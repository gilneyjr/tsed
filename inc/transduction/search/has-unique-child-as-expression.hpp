#ifndef HAS_UNIQUE_CHILD_AS_EXPRESSION_HPP
#define HAS_UNIQUE_CHILD_AS_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class HasUniqueChildAsExpression : public SearchExpression
  {
  private:
    SearchExpression* expression;
  public:
    HasUniqueChildAsExpression(SearchExpression*);
    ~HasUniqueChildAsExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
