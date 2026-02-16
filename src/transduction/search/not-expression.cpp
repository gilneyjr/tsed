#include "not-expression.hpp"

Transduction::Search::NotExpression::NotExpression(OperationExpression *operationExpression)
  : operationExpression(operationExpression) {}

Transduction::Search::NotExpression::~NotExpression()
{
  if (!operationExpression)
    delete operationExpression;
}

bool Transduction::Search::NotExpression::match(Contexts::SearchMatchContext &context) const
{
  context.symbolTable->enterScope();
  bool matched = !operationExpression->match(context);
  context.symbolTable->exitScope(); // all matches found in negation are discarded
  return matched;
}

void Transduction::Search::NotExpression::validate(Contexts::SearchValidationContext &context) const
{
  if (!operationExpression)
  {
    context.errors.emplace_back("Malformed search expression: not expression must have a sub expression to be matched in syntax tree search.");
    return;
  }

  operationExpression->validate(context);
}