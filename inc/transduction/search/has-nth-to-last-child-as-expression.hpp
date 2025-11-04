#ifndef HAS_NTH_TO_LAST_CHILD_AS_EXPRESSION_HPP
#define HAS_NTH_TO_LAST_CHILD_AS_EXPRESSION_HPP

#include "search-expression.hpp"

namespace Transduction::Search
{
  class HasNthToLastChildAsExpression : public SearchExpression
  {
  private:
    unsigned int n;
    SearchExpression* expression;
  public:
    HasNthToLastChildAsExpression(unsigned int, SearchExpression*);
    ~HasNthToLastChildAsExpression();
    bool match(SyntaxTree*, SymbolTable&);
  };
}

#endif
