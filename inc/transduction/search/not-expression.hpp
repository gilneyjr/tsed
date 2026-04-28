#ifndef NOT_EXPRESSION_HPP
#define NOT_EXPRESSION_HPP

#include "operation-expression.hpp"

namespace Transduction::Search
{
  class NotExpression : public OperationExpression
  {
  private:
    OperationExpression *operationExpression;
  public:
    NotExpression(OperationExpression*);
    ~NotExpression();
    bool match(Contexts::SearchMatchContext&) const override;
    void validate(Contexts::SearchValidationContext&) const override;
    void print(int tab = 0) override;
  };
}

#endif
