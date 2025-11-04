#ifndef HAS_UNIQUE_PATH_TO_EXPRESSION_HPP
#define HAS_UNIQUE_PATH_TO_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class HasUniquePathToExpression : public SearchExpression
  {
  private:
    SearchExpression* expression;
  public:
    HasUniquePathToExpression(SearchExpression*);
    ~HasUniquePathToExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
