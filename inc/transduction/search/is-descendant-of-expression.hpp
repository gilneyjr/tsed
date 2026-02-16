#ifndef IS_DESCENDANT_OF_EXPRESSION_HPP
#define IS_DESCENDANT_OF_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class IsDescendantOfExpression : public RestrictionExpression
  {
  public:
    IsDescendantOfExpression(SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
    virtual void validate(Contexts::SearchValidationContext&) const override;
  };
}

#endif
