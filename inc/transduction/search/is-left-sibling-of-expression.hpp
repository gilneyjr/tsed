#ifndef IS_LEFT_SIBLING_OF_EXPRESSION_HPP
#define IS_LEFT_SIBLING_OF_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class IsLeftSiblingOfExpression : public SearchExpression
  {
  private:
    SearchExpression* expression;
  public:
    IsLeftSiblingOfExpression(SearchExpression*);
    ~IsLeftSiblingOfExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
