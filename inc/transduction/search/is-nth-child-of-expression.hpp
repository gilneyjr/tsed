#ifndef IS_NTH_CHILD_OF_EXPRESSION_HPP
#define IS_NTH_CHILD_OF_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class IsNthChildOfExpression : public SearchExpression
  {
  private:
    unsigned int n;
    SearchExpression* expression;
  public:
    IsNthChildOfExpression(unsigned int, SearchExpression*);
    ~IsNthChildOfExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
