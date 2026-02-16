#ifndef IS_RIGHTMOST_DESCENDANT_OF_EXPRESSION_HPP
#define IS_RIGHTMOST_DESCENDANT_OF_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class IsRightmostDescendantOfExpression : public RestrictionExpression
  {
  public:
    IsRightmostDescendantOfExpression(SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
    virtual void validate(Contexts::SearchValidationContext&) const override;
  };
}

#endif
