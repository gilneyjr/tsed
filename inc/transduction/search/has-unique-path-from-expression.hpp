#ifndef HAS_UNIQUE_PATH_FROM_EXPRESSION_HPP
#define HAS_UNIQUE_PATH_FROM_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class HasUniquePathFromExpression : public RestrictionExpression
  {
  public:
    HasUniquePathFromExpression(SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
    virtual void validate(Contexts::SearchValidationContext&) const override;
  };
}

#endif
