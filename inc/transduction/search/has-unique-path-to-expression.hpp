#ifndef HAS_UNIQUE_PATH_TO_EXPRESSION_HPP
#define HAS_UNIQUE_PATH_TO_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class HasUniquePathToExpression : public RestrictionExpression
  {
  public:
    HasUniquePathToExpression(SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
    virtual void validate(Contexts::SearchValidationContext&) const override;
  };
}

#endif
