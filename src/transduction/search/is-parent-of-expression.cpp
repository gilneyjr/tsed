#include "is-parent-of-expression.hpp"

Transduction::Search::IsParentOfExpression::IsParentOfExpression(SearchExpression *expression)
  : RestrictionExpression(expression) {}

bool Transduction::Search::IsParentOfExpression::match(Contexts::SearchMatchContext &context) const
{
  if (context.matched->getFirstChild() == nullptr)
  {
    // try to match right side of restriction with end marker
    auto child = SyntaxTree::createEndMarkerBellow(context.matched);
    return expression->match(Contexts::SearchMatchContext(child, context.symbolTable, true));
  }

  for (auto child = context.matched->getFirstChild(); child != nullptr; child = child->getRightSibling())
    if (expression->match(Contexts::SearchMatchContext(child, context.symbolTable)))
      return true;
  return false;
}
