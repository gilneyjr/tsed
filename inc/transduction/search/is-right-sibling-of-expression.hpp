#ifndef IS_RIGHT_SIBLING_OF_EXPRESSION_HPP
#define IS_RIGHT_SIBLING_OF_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class IsRightSiblingOfExpression : public SearchExpression
  {
  private:
    SearchExpression* expression;
  public:
    IsRightSiblingOfExpression(SearchExpression*);
    ~IsRightSiblingOfExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
