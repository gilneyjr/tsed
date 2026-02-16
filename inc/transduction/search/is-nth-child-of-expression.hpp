#ifndef IS_NTH_CHILD_OF_EXPRESSION_HPP
#define IS_NTH_CHILD_OF_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class IsNthChildOfExpression : public RestrictionExpression
  {
  private:
    unsigned int n;
  public:
    IsNthChildOfExpression(unsigned int, SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
    virtual void validate(Contexts::SearchValidationContext&) const override;
  };
}

#endif
