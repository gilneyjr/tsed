#ifndef IS_PARENT_OF_EXPRESSION_HPP
#define IS_PARENT_OF_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class IsParentOfExpression : public RestrictionExpression
  {
  public:
    IsParentOfExpression(SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
  };
}

#endif
