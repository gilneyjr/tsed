#include "has-nth-child-as-expression.hpp"

Transduction::Search::HasNthChildAsExpression::HasNthChildAsExpression(unsigned int n, SearchExpression *expression)
  : RestrictionExpression(expression), n(n) {}

bool Transduction::Search::HasNthChildAsExpression::match(Contexts::SearchMatchContext &context) const
{
  if (context.matchedIsEndMarker || context.matched->getFirstChild() == nullptr || n == 0)
    return false;

  auto nthChild = context.matched->getFirstChild();
  for (auto i = 1u; i < n; i++)
  {
    nthChild = nthChild->getRightSibling();
    if (nthChild == nullptr)
      return false;
  }

  return expression->match(Contexts::SearchMatchContext(nthChild, context.symbolTable));
}

void Transduction::Search::HasNthChildAsExpression::validate(Contexts::SearchValidationContext &context) const
{
  bool leftIsEndMarker = context.leftIsEndMarker;
  bool rightIsEndMarker = expression != nullptr && expression->leftIsEndMarker();

  if (leftIsEndMarker || rightIsEndMarker)
  {
    context.errors.emplace_back("Error in search expression: operators \"<,\" and \"<N\" cannot operate on an end marker.");
    return;
  }

  RestrictionExpression::validate(context);
}

