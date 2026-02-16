#ifndef IS_ANCESTOR_OF_EXPRESSION_HPP
#define IS_ANCESTOR_OF_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class IsAncestorOfExpression : public RestrictionExpression
  {
  public:
    IsAncestorOfExpression(SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
    virtual void validate(Contexts::SearchValidationContext&) const override;
  };
}

#endif
