#ifndef IS_PARENT_OF_EXPRESSION_HPP
#define IS_PARENT_OF_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class IsParentOfExpression : public SearchExpression
  {
  private:
    SearchExpression* expression;
  public:
    IsParentOfExpression(SearchExpression*);
    ~IsParentOfExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
