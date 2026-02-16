#include "is-nth-child-of-expression.hpp"

Transduction::Search::IsNthChildOfExpression::IsNthChildOfExpression(unsigned int n, SearchExpression *expression)
  : RestrictionExpression(expression), n(n) {}

bool Transduction::Search::IsNthChildOfExpression::match(Contexts::SearchMatchContext &context) const
{
  if (context.matchedIsEndMarker
    || context.matched->getParent() == nullptr
    || context.matched->getParent()->getFirstChild() != nullptr
    || n == 0u
  )
  {
    return false;
  }

  auto nthChildOfParent = context.matched->getParent()->getFirstChild();
  for (auto i = 1u; i < n; i++)
  {
    nthChildOfParent = nthChildOfParent->getRightSibling();
    if (nthChildOfParent == nullptr)
      return false;
  }

  return nthChildOfParent == context.matched
    && expression->match(Contexts::SearchMatchContext(context.matched->getParent(), context.symbolTable));
}

void Transduction::Search::IsNthChildOfExpression::validate(Contexts::SearchValidationContext &context) const
{
  bool leftIsEndMarker = context.leftIsEndMarker;
  bool rightIsEndMarker = expression != nullptr && expression->leftIsEndMarker();

  if (leftIsEndMarker || rightIsEndMarker)
  {
    context.errors.emplace_back("Error in search expression: operators \">,\" and \">N\" cannot operate on an end marker.");
    return;
  }

  RestrictionExpression::validate(context);
}
