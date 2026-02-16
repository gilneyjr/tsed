#include "has-leftmost-descendant-as-expression.hpp"
#include "syntax-tree.hpp"

Transduction::Search::HasLeftmostDescendantAsExpression::HasLeftmostDescendantAsExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}


bool Transduction::Search::HasLeftmostDescendantAsExpression::match(Contexts::SearchMatchContext &context) const
{
  if (context.matchedIsEndMarker || context.matched->getFirstChild() == nullptr)
   return false;

  auto leftmostDescendant = context.matched->getFirstChild();
  while (leftmostDescendant->getFirstChild() != nullptr)
    leftmostDescendant = leftmostDescendant->getFirstChild();

  return expression->match(Contexts::SearchMatchContext(leftmostDescendant, context.symbolTable));
}

void Transduction::Search::HasLeftmostDescendantAsExpression::validate(Contexts::SearchValidationContext &context) const
{
  bool leftIsEndMarker = context.leftIsEndMarker;
  bool rightIsEndMarker = expression != nullptr && expression->leftIsEndMarker();

  if (leftIsEndMarker || rightIsEndMarker)
  {
    context.errors.emplace_back("Error in search expression: operator \"<<,\" cannot operate on an end marker.");
    return;
  }

  RestrictionExpression::validate(context);
}
