#ifndef IS_SIBLING_OF_EXPRESSION_HPP
#define IS_SIBLING_OF_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class IsSiblingOfExpression : public SearchExpression
  {
  private:
    SearchExpression* expression;
  public:
    IsSiblingOfExpression(SearchExpression*);
    ~IsSiblingOfExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
