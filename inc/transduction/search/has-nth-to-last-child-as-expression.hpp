#ifndef HAS_NTH_TO_LAST_CHILD_AS_EXPRESSION_HPP
#define HAS_NTH_TO_LAST_CHILD_AS_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class HasNthToLastChildAsExpression : public RestrictionExpression
  {
  private:
    unsigned int n;
  public:
    HasNthToLastChildAsExpression(unsigned int, SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
    virtual void validate(Contexts::SearchValidationContext&) const override;
  };
}

#endif
