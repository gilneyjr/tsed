#ifndef IS_IMMEDIATELY_RIGHT_SIBLING_OF_EXPRESSION_HPP
#define IS_IMMEDIATELY_RIGHT_SIBLING_OF_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class IsImmediatelyRightSiblingOfExpression : public RestrictionExpression
  {
  public:
    IsImmediatelyRightSiblingOfExpression(SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
  };
}

#endif
