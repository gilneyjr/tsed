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
    SearchExpression(
      NodenameExpression *nodenameExpression, 
      OperationExpression *operationExpression = nullptr
    );
    ~SearchExpression();
    bool leftIsEndMarker() const;
    bool leftIsSubtreeRange() const;
    bool match(Contexts::SearchMatchContext &&context) const;
    bool match(Contexts::SearchMatchContext &context) const;
    void validate(Contexts::SearchValidationContext &context) const;

    // TODO: remove it later
    void print(int tab = 0);
  };
}

#endif
