#include "nodename-info.hpp"
#include "or-expression.hpp"

Transduction::Search::OrExpression::OrExpression(OperationExpression *leftExpression, OperationExpression *rightExpression)
  : leftExpression(leftExpression), rightExpression(rightExpression) {}

Transduction::Search::OrExpression::~OrExpression()
{
  if (leftExpression)
    delete leftExpression;
  if (rightExpression)
    delete rightExpression;
}

bool Transduction::Search::OrExpression::match(Contexts::SearchMatchContext &context) const
{
  context.symbolTable->enterScope();
  
  bool matched = leftExpression->match(context) || rightExpression->match(context);

  if (matched)
    return true;

  context.symbolTable->exitScope();
  return false;
}

void Transduction::Search::OrExpression::validate(Contexts::SearchValidationContext &context) const
{
  if (!leftExpression || !rightExpression)
  {
    if (!leftExpression)
      context.errors.emplace_back("Malformed search expression: a or operation must have a left restriction.");

    if (!rightExpression)
      context.errors.emplace_back("Malformed search expression: a or operation must have a right restriction.");

    return;
  }

  Contexts::SearchValidationContext &leftContext = context;
  Contexts::SearchValidationContext rightContext;

  leftExpression->validate(leftContext);
  rightExpression->validate(rightContext);

  if (leftContext.errors.size() > 0 || rightContext.errors.size() > 0)
    return;

  auto &leftDefinitions = leftContext.definitions;
  auto &leftReferences = leftContext.references;
  auto &rightDefinitions = rightContext.definitions;
  auto &rightReferences = rightContext.references;

  for (auto [leftDefKey, leftDef] : leftDefinitions)
  {
    auto rightDefIt = rightDefinitions.find(leftDefKey);
    auto rightRefIt = rightReferences.find(leftDefKey);

    if (rightDefIt != rightDefinitions.end()) // def x def
    {
      if (leftDef->placeholder != rightDefIt->second->placeholder)
      {
        // TODO: Correct/Improve this error message
        context.errors.emplace_back("The nodename definition must have the same placeholder type in every sides of the OR operator.");
        return; // TODO: Verify if it needs to return here
      }
      else
        context.definitions.insert({leftDefKey, leftDef});
    } 
    else if (rightRefIt != rightReferences.end()) // def x ref
    {
      // TODO: Correct/Improve this error message
      context.errors.emplace_back("The node name reference is not being defined on the side of the OR operator where it is used.");
      return; // TODO: Verify if it needs to return here
    }
    else // def x ---
    {
      // TODO: Correct/Improve this warning message
      context.warnings.emplace_back("The nodename definition is not present on every side of the OR operator, so it will not be accessible outside the side where it is defined.");
    }
  }

  for (auto [leftRefKey, leftRef] : leftReferences)
  {
    auto rightDefIt = rightDefinitions.find(leftRefKey);
    auto rightRefIt = rightReferences.find(leftRefKey);

    if (rightDefIt != rightDefinitions.end()) // ref x def
    {
      // TODO: Correct/Improve this error message
      context.errors.emplace_back("The node name reference is not being defined on the side of the OR operator where it is used.");
      return; // TODO: Verify if it needs to return here
    }
    else if (rightRefIt != rightReferences.end()) // ref x ref
    {
      if (leftRef->placeholder != rightRefIt->second->placeholder)
      {
        // TODO: Correct/Improve this error message  
        context.errors.emplace_back("The nodename reference must have the same placeholder type in every sides of the OR operator.");
        return; // TODO: Verify if it needs to return here
      }
      else
        context.references.insert({leftRefKey, leftRef});
    }
    else // ref x ---
    {
      // TODO: Correct/Improve this error message
      context.errors.emplace_back("The nodename reference is not present on every side of the OR operator, resulting in an unresolved reference.");
      return; // TODO: Verify if it needs to return here
    }
  }

  for (auto [rightDefKey, rightDef] : rightDefinitions)
  {
    auto leftDefIt = leftDefinitions.find(rightDefKey);
    auto leftRefIt = leftReferences.find(rightDefKey);

    if (leftDefIt == leftDefinitions.end() && leftRefIt == leftReferences.end()) // --- x def
    {
      // TODO: Correct/Improve this error message
      context.errors.emplace_back("The nodename definition is not present on every side of the OR operator, so it will not be accessible outside the side where it is defined.");
      return; // TODO: Verify if it needs to return here
    }
  }

  for (auto [rightRefKey, rightRef] : rightReferences)
  {
    auto leftDefIt = leftDefinitions.find(rightRefKey);
    auto leftRefIt = leftReferences.find(rightRefKey);

    if (leftDefIt == leftDefinitions.end() && leftRefIt == leftReferences.end()) // --- x ref
    {
      // TODO: Correct/Improve this error message
      context.errors.emplace_back("The nodename reference is not present on every side of the OR operator, resulting in an unresolved reference.");
      return; // TODO: Verify if it needs to return here
    }
  }
}

// TODO: Remove it later
#include <iostream>
void Transduction::Search::OrExpression::print(int tab)
{
  for (int i = 1; i <= tab; i++)
    std::cout << "  ";
  std::cout << "OR" << std::endl;
  leftExpression->print(tab + 1);
  rightExpression->print(tab + 1);
}
