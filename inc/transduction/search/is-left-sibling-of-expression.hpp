#ifndef IS_LEFT_SIBLING_OF_EXPRESSION_HPP
#define IS_LEFT_SIBLING_OF_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class IsLeftSiblingOfExpression : public RestrictionExpression
  {
  public:
    IsLeftSiblingOfExpression(SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
    virtual void validate(Contexts::SearchValidationContext&) const override;
  };
}

#endif
