#ifndef SEARCH_EXPRESSION_HPP
#define SEARCH_EXPRESSION_HPP

#include "nodename-expression.hpp"
#include "search-match-context.hpp"
#include "search-validation-context.hpp"
#include "operation-expression.hpp"

namespace Transduction::Search
{
  class SearchExpression
  {
  private:
    NodenameExpression* nodenameExpression;
    OperationExpression* operationExpression;
  public:
    SearchExpression(NodenameExpression*, OperationExpression* = nullptr);
    ~SearchExpression();
    bool leftIsEndMarker() const;
    bool match(Contexts::SearchMatchContext&&) const;
    bool match(Contexts::SearchMatchContext&) const;
    void validate(Contexts::SearchValidationContext&) const;
  };
}

#endif
