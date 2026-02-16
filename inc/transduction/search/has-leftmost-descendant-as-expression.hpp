#ifndef HAS_LEFTMOST_DESCENDANT_AS_EXPRESSION_HPP
#define HAS_LEFTMOST_DESCENDANT_AS_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class HasLeftmostDescendantAsExpression : public RestrictionExpression
  {
  public:
    HasLeftmostDescendantAsExpression(SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
    virtual void validate(Contexts::SearchValidationContext&) const override;
  };
}

#endif
