#ifndef IS_RIGHT_SIBLING_OF_EXPRESSION_HPP
#define IS_RIGHT_SIBLING_OF_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class IsRightSiblingOfExpression : public RestrictionExpression
  {
  public:
    IsRightSiblingOfExpression(SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
    virtual void validate(Contexts::SearchValidationContext&) const override;
  };
}

#endif
