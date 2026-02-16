#include "has-nth-to-last-child-as-expression.hpp"

Transduction::Search::HasNthToLastChildAsExpression::HasNthToLastChildAsExpression(unsigned int n, SearchExpression *expression)
  : RestrictionExpression(expression), n(n) {}

bool Transduction::Search::HasNthToLastChildAsExpression::match(Contexts::SearchMatchContext &context) const
{
  if (context.matchedIsEndMarker || context.matched->getLastChild() == nullptr || n == 0)
    return false;

  auto nthToLastChild = context.matched->getLastChild();
  for (auto i = 1u; i < n; i++)
  {
    nthToLastChild = nthToLastChild->getLeftSibling();
    if (nthToLastChild == nullptr)
      return false;
  }

  return expression->match(Contexts::SearchMatchContext(nthToLastChild, context.symbolTable));
}

void Transduction::Search::HasNthToLastChildAsExpression::validate(Contexts::SearchValidationContext &context) const
{
  bool leftIsEndMarker = context.leftIsEndMarker;
  bool rightIsEndMarker = expression != nullptr && expression->leftIsEndMarker();

  if (leftIsEndMarker || rightIsEndMarker)
  {
    context.errors.emplace_back("Error in search expression: operators \"<'\", \"<-\" and \"<-N\" cannot operate on an end marker.");
    return;
  }

  RestrictionExpression::validate(context);
}
