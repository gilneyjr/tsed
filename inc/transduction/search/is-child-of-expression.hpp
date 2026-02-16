#ifndef IS_CHILD_OF_EXPRESSION_HPP
#define IS_CHILD_OF_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class IsChildOfExpression : public RestrictionExpression
  {
  public:
    IsChildOfExpression(SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
  };
}

#endif
