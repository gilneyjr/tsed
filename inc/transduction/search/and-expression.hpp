#ifndef AND_EXPRESSION_HPP
#define AND_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class AndExpression : public SearchExpression
  {
  private:
    SearchExpression* leftExpression;
    SearchExpression* rightExpression;
  public:
    AndExpression(SearchExpression*, SearchExpression*);
    ~AndExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
