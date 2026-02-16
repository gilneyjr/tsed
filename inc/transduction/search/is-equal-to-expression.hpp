#ifndef IS_EQUAL_TO_EXPRESSION_HPP
#define IS_EQUAL_TO_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class IsEqualToExpression : public RestrictionExpression
  {
  public:
    IsEqualToExpression(SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
    virtual void validate(Contexts::SearchValidationContext&) const override;
  };
}

#endif
