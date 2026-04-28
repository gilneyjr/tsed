#include "restriction-expression.hpp"

Transduction::Search::RestrictionExpression::RestrictionExpression(SearchExpression *expression)
  : expression(expression) {}

Transduction::Search::RestrictionExpression::~RestrictionExpression()
{
  if (expression)
    delete expression;
}

void Transduction::Search::RestrictionExpression::validate(Contexts::SearchValidationContext &context) const
{
  if (!expression)
  {
    context.errors.emplace_back("Malformed search expression: a restriction must have a subexpression to which the restrictions are applied during the syntax tree search.");
    return;
  }

  bool leftIsEndMarker = context.leftIsEndMarker;
  bool rightIsEndMarker = expression->leftIsEndMarker();

  if (leftIsEndMarker && rightIsEndMarker)
  {
    context.errors.emplace_back("Invalid search expression: end marker cannot operate on another endmarker.");
    return;
  }

  expression->validate(context);
}

// TODO: Remove it later
#include <iostream>
void Transduction::Search::RestrictionExpression::print(int tab)
{
  for (int i = 1; i <= tab; i++)
    std::cout << "  ";
  std::cout << "OP" << std::endl;
  expression->print(tab + 1);
}
