#ifndef IS_NTH_TO_LAST_CHILD_OF_EXPRESSION_HPP
#define IS_NTH_TO_LAST_CHILD_OF_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class IsNthToLastChildOfExpression : public SearchExpression
  {
  private:
    unsigned int n;
    SearchExpression* expression;
  public:
    IsNthToLastChildOfExpression(unsigned int, SearchExpression*);
    ~IsNthToLastChildOfExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
