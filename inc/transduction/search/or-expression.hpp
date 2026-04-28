#ifndef Or_EXPRESSION_HPP
#define Or_EXPRESSION_HPP

#include "operation-expression.hpp"
#include "search-match-context.hpp"
#include "search-validation-context.hpp"

namespace Transduction::Search
{
  class OrExpression : public OperationExpression
  {
  private:
    OperationExpression* leftExpression;
    OperationExpression* rightExpression;
  public:
    OrExpression(OperationExpression*, OperationExpression*);
    ~OrExpression();
    bool match(Contexts::SearchMatchContext&) const override;
    void validate(Contexts::SearchValidationContext&) const override;
    void print(int tab = 0) override;
  };
}

#endif
