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

bool Transduction::Search::SearchExpression::leftIsSubtreeRange() const
{
  return nodenameExpression != nullptr && nodenameExpression->isSubtreeRange();
}

bool Transduction::Search::SearchExpression::match(Contexts::SearchMatchContext &&context) const
{
  return match(context);
}

bool Transduction::Search::SearchExpression::match(Contexts::SearchMatchContext &context) const
{
  if (nodenameExpression == nullptr || context.current == nullptr)
    return false;

  auto nodenameContext = Contexts::SearchMatchContext(context);

  if (!nodenameExpression->match(nodenameContext))
    return false;

  nodenameContext.matchedIsEndMarker = nodenameExpression->isEndMarker();
  nodenameContext.matched = nodenameContext.current;

  return operationExpression == nullptr || operationExpression->match(nodenameContext);
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
  {
    if (nodenameExpression->isSubtreeRange())
    {
      context.errors.emplace_back("Malformed search expression: subtree range captures cannot appear on the left-hand side of a restriction.");
      return;
    }
    operationExpression->validate(context);
  }
  context.leftIsEndMarker = tmp;
}

// TODO: Remove it later
#include <iostream>
void Transduction::Search::SearchExpression::print(int tab)
{
  for (int i = 1; i <= tab; i++)
    std::cout << "  ";
  std::cout << ":> " << std::endl;
  nodenameExpression->print(tab + 1);
  if (operationExpression != nullptr)
    operationExpression->print(tab + 1);
}