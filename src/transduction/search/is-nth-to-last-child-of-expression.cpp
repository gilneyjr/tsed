#include "is-nth-to-last-child-of-expression.hpp"

Transduction::Search::IsNthToLastChildOfExpression::IsNthToLastChildOfExpression(unsigned int n, SearchExpression *expression)
  : RestrictionExpression(expression), n(n) {}

bool Transduction::Search::IsNthToLastChildOfExpression::match(Contexts::SearchMatchContext &context) const
{
  if (context.matchedIsEndMarker
    || context.matched->getParent() == nullptr
    || context.matched->getParent()->getLastChild() == nullptr
    || n == 0
  )
  {
    return false;
  }

  auto nthToLastChildOfParent = context.matched->getParent()->getLastChild();
  for (auto i = n; i > 1u; i--)
  {
    nthToLastChildOfParent = nthToLastChildOfParent->getLeftSibling();
    if (nthToLastChildOfParent == nullptr)
      return false;
  }

  return nthToLastChildOfParent == context.matched
    && expression->match(Contexts::SearchMatchContext(context.matched->getParent(), context.symbolTable));
}

void Transduction::Search::IsNthToLastChildOfExpression::validate(Contexts::SearchValidationContext &context) const
{
  bool leftIsEndMarker = context.leftIsEndMarker;
  bool rightIsEndMarker = expression != nullptr && expression->leftIsEndMarker();

  if (leftIsEndMarker || rightIsEndMarker)
  {
    context.errors.emplace_back("Error in search expression: operators \">'\", \">-\" and \">-N\" cannot operate on an end marker.");
    return;
  }

  RestrictionExpression::validate(context);
}
