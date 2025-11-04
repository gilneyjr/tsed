#ifndef IS_IMMEDIATELY_LEFT_SIBLING_OF_EXPRESSION_HPP
#define IS_IMMEDIATELY_LEFT_SIBLING_OF_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class IsImmediatelyLeftSiblingOfExpression : public SearchExpression
  {
  private:
    SearchExpression* expression;
  public:
    IsImmediatelyLeftSiblingOfExpression(SearchExpression*);
    ~IsImmediatelyLeftSiblingOfExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
