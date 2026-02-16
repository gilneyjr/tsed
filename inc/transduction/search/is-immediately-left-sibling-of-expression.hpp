#ifndef IS_IMMEDIATELY_LEFT_SIBLING_OF_EXPRESSION_HPP
#define IS_IMMEDIATELY_LEFT_SIBLING_OF_EXPRESSION_HPP

#include "restriction-expression.hpp"

namespace Transduction::Search
{
  class IsImmediatelyLeftSiblingOfExpression : public RestrictionExpression
  {
  public:
    IsImmediatelyLeftSiblingOfExpression(SearchExpression*);
    virtual bool match(Contexts::SearchMatchContext&) const override;
  };
}

#endif
