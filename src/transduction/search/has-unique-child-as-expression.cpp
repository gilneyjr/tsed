#include "has-unique-child-as-expression.hpp"

Transduction::Search::HasUniqueChildAsExpression::HasUniqueChildAsExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}

bool Transduction::Search::HasUniqueChildAsExpression::match(Contexts::SearchMatchContext &context) const
{
  if (context.matchedIsEndMarker 
    || context.matched->getFirstChild() == nullptr
    || context.matched->getFirstChild() != context.matched->getLastChild()
  )
  {
    return false;
  }

  return expression->match(Contexts::SearchMatchContext(context.matched->getFirstChild(), context.symbolTable));
}

void Transduction::Search::HasUniqueChildAsExpression::validate(Contexts::SearchValidationContext &context) const
{
  bool leftIsEndMarker = context.leftIsEndMarker;
  bool rightIsEndMarker = expression != nullptr && expression->leftIsEndMarker();

  if (leftIsEndMarker || rightIsEndMarker)
  {
    context.errors.emplace_back("Error in search expression: operator \"<:\" cannot operate on an end marker.");
    return;
  }

  RestrictionExpression::validate(context);
}
