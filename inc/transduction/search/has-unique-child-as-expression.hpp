#ifndef HAS_UNIQUE_CHILD_AS_EXPRESSION_HPP
#define HAS_UNIQUE_CHILD_AS_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class HasUniqueChildAsExpression : public RestrictionExpression
  {
  public:
    HasUniqueChildAsExpression(SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
    virtual void validate(Contexts::SearchValidationContext&) const override;
  };
}

#endif
