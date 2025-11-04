#ifndef IS_ANCESTOR_OF_EXPRESSION_HPP
#define IS_ANCESTOR_OF_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class IsAncestorOfExpression : public SearchExpression
  {
  private:
    SearchExpression* expression;
  public:
    IsAncestorOfExpression(SearchExpression*);
    ~IsAncestorOfExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
