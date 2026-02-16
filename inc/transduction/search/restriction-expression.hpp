#ifndef RESTRICTION_EXPRESSION_HPP
#define RESTRICTION_EXPRESSION_HPP

#include "operation-expression.hpp"
#include "search-expression.hpp"
#include "search-match-context.hpp"
#include "search-validation-context.hpp"

namespace Transduction::Search
{
  class RestrictionExpression : public OperationExpression
  {
  protected:
    SearchExpression* expression;
  public:
    RestrictionExpression(SearchExpression*);
    virtual ~RestrictionExpression();
    virtual void validate(Contexts::SearchValidationContext&) const override;
  };
}

#endif
