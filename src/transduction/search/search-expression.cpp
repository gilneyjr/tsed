#include "search-expression.hpp"

Transduction::Search::SearchExpression::SearchExpression(
  NodenameExpression *nodenameExpression, OperationExpression *operationExpression
) : nodenameExpression(nodenameExpression), operationExpression(operationExpression) {}

Transduction::Search::SearchExpression::~SearchExpression()
{
  if (nodenameExpression != nullptr)
    delete nodenameExpression;
  if (operationExpression != nullptr)
    delete operationExpression;
}

bool Transduction::Search::SearchExpression::leftIsEndMarker() const
{
  return nodenameExpression != nullptr && nodenameExpression->isEndMarker();
}

bool Transduction::Search::SearchExpression::match(Contexts::SearchMatchContext &&context) const
{
  return match(context);
}

bool Transduction::Search::SearchExpression::match(Contexts::SearchMatchContext &context) const
{
  if (!nodenameExpression || !nodenameExpression->match(context))
    return false;

  if (!operationExpression)
    return true;

  // TODO: set end marker flag in the context here
  return operationExpression->match(context);
}

void Transduction::Search::SearchExpression::validate(Contexts::SearchValidationContext &context) const
{
  if (!nodenameExpression)
  {
    context.errors.emplace_back("Malformed search expression: search expression must have a left-hand side in order to be used in the syntax tree search.");
    return;
  }
  
  nodenameExpression->validate(context);

  auto tmp = context.leftIsEndMarker;
  context.leftIsEndMarker = leftIsEndMarker();
  if (operationExpression)
    operationExpression->validate(context);
  context.leftIsEndMarker = tmp;
}
