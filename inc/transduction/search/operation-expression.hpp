#ifndef OPERATION_EXPRESSION_HPP
#define OPERATION_EXPRESSION_HPP

#include "search-match-context.hpp"
#include "search-validation-context.hpp"

namespace Transduction::Search
{
  class OperationExpression
  {
  public:
    virtual ~OperationExpression();
    virtual bool match(Contexts::SearchMatchContext&) const = 0;
    virtual void validate(Contexts::SearchValidationContext&) const = 0;
    virtual void print(int tab) = 0;
  };
}

#endif
