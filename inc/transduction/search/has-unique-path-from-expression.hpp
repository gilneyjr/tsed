#ifndef HAS_UNIQUE_PATH_FROM_EXPRESSION_HPP
#define HAS_UNIQUE_PATH_FROM_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class HasUniquePathFromExpression : public SearchExpression
  {
  private:
    SearchExpression* expression;
  public:
    HasUniquePathFromExpression(SearchExpression*);
    ~HasUniquePathFromExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
