#ifndef Or_EXPRESSION_HPP
#define Or_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class OrExpression : public SearchExpression
  {
  private:
    SearchExpression* leftExpression;
    SearchExpression* rightExpression;
  public:
    OrExpression(SearchExpression*, SearchExpression*);
    ~OrExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
