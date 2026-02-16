#ifndef HAS_RIGHTMOST_DESCENDANT_AS_EXPRESSION_HPP
#define HAS_RIGHTMOST_DESCENDANT_AS_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class HasRightmostDescendantAsExpression : public RestrictionExpression
  {
  public:
    HasRightmostDescendantAsExpression(SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
    virtual void validate(Contexts::SearchValidationContext&) const override;
  };
}

#endif
