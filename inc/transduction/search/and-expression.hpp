#ifndef AND_EXPRESSION_HPP
#define AND_EXPRESSION_HPP

#include "operation-expression.hpp"
#include "search-match-context.hpp"
#include "search-validation-context.hpp"

namespace Transduction::Search
{
  class AndExpression : public OperationExpression
  {
  private:
    OperationExpression* leftExpression;
    OperationExpression* rightExpression;
  public:
    AndExpression(OperationExpression*, OperationExpression*);
    ~AndExpression();
    bool match(Contexts::SearchMatchContext&) const override;
    void validate(Contexts::SearchValidationContext&) const override;
    void print(int tab = 0) override;
  };
}

#endif
