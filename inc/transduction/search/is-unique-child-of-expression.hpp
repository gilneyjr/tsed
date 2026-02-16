#ifndef IS_UNIQUE_CHILD_OF_EXPRESSION_HPP
#define IS_UNIQUE_CHILD_OF_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class IsUniqueChildOfExpression : public RestrictionExpression
  {
  public:
    IsUniqueChildOfExpression(SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
    virtual void validate(Contexts::SearchValidationContext&) const override;
  };
}

#endif
