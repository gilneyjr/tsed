#ifndef NOT_EXPRESSION_HPP
#define NOT_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class NotExpression : public SearchExpression
  {
  private:
    SearchExpression* expression;
  public:
    NotExpression(SearchExpression*);
    ~NotExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
