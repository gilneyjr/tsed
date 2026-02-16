#ifndef IS_LEFTMOST_DESCENDANT_OF_EXPRESSION_HPP
#define IS_LEFTMOST_DESCENDANT_OF_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class IsLeftmostDescendantOfExpression : public RestrictionExpression
  {
  public:
    IsLeftmostDescendantOfExpression(SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
    virtual void validate(Contexts::SearchValidationContext&) const override;
  };
}

#endif
