#ifndef IS_IMMEDIATELY_RIGHT_SIBLING_OF_EXPRESSION_HPP
#define IS_IMMEDIATELY_RIGHT_SIBLING_OF_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class IsImmediatelyRightSiblingOfExpression : public SearchExpression
  {
  private:
    SearchExpression* expression;
  public:
    IsImmediatelyRightSiblingOfExpression(SearchExpression*);
    ~IsImmediatelyRightSiblingOfExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
