#ifndef IS_NTH_TO_LAST_CHILD_OF_EXPRESSION_HPP
#define IS_NTH_TO_LAST_CHILD_OF_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class IsNthToLastChildOfExpression : public RestrictionExpression
  {
  private:
    unsigned int n;
  public:
    IsNthToLastChildOfExpression(unsigned int, SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
    virtual void validate(Contexts::SearchValidationContext&) const override;
  };
}

#endif
