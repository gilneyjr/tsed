#ifndef HAS_NTH_CHILD_AS_EXPRESSION_HPP
#define HAS_NTH_CHILD_AS_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class HasNthChildAsExpression : public RestrictionExpression
  {
  private:
    unsigned int n;
  public:
    HasNthChildAsExpression(unsigned int, SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
    virtual void validate(Contexts::SearchValidationContext&) const override;
  };
}

#endif
