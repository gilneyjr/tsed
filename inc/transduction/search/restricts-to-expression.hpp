#ifndef RESTRICTS_TO_EXPRESSION_HPP
#define RESTRICTS_TO_EXPRESSION_HPP

#include "search-expression.hpp"
#include "nodename-expression.hpp"

namespace Transduction::Search
{
  class RestrictsToExpression : public SearchExpression
  {
  private:
    NodenameExpression* nodenameExpression;
    SearchExpression* restrictionsExpression;
  public:
    RestrictsToExpression(NodenameExpression*, SearchExpression*);
    ~RestrictsToExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
