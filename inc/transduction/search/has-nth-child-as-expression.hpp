#ifndef HAS_NTH_CHILD_AS_EXPRESSION_HPP
#define HAS_NTH_CHILD_AS_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class HasNthChildAsExpression : public SearchExpression
  {
  private:
    unsigned int n;
    SearchExpression* expression;
  public:
    HasNthChildAsExpression(unsigned int, SearchExpression*);
    ~HasNthChildAsExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
