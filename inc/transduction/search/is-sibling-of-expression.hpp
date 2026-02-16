#ifndef IS_SIBLING_OF_EXPRESSION_HPP
#define IS_SIBLING_OF_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class IsSiblingOfExpression : public RestrictionExpression
  {
  public:
    IsSiblingOfExpression(SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
    virtual void validate(Contexts::SearchValidationContext&) const override;
  };
}

#endif
