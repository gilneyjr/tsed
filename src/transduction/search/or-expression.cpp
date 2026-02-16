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

  for (auto *leftDef : leftDefinitions)
  {
    auto rightDefIt = rightDefinitions.find(leftDef);
    auto rightRefIt = rightReferences.find(leftDef);

    if (rightDefIt != rightDefinitions.end()) // def x def
    {
      if (leftDef->placeholder != (*rightDefIt)->placeholder)
      {
        // TODO: Correct/Improve this error message
        context.errors.emplace_back("The nodename definition must have the same placeholder type in every sides of the OR operator.");
        return; // TODO: Verify if it needs to return here
      }
      else
        context.definitions.insert(leftDef);
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

  for (auto *leftRef : leftReferences)
  {
    auto rightDefIt = rightDefinitions.find(leftRef);
    auto rightRefIt = rightReferences.find(leftRef);

    if (rightDefIt != rightDefinitions.end()) // ref x def
    {
      // TODO: Correct/Improve this error message
      context.errors.emplace_back("The node name reference is not being defined on the side of the OR operator where it is used.");
      return; // TODO: Verify if it needs to return here
    }
    else if (rightRefIt != rightReferences.end()) // ref x ref
    {
      if (leftRef->placeholder != (*rightRefIt)->placeholder)
      {
        // TODO: Correct/Improve this error message  
        context.errors.emplace_back("The nodename reference must have the same placeholder type in every sides of the OR operator.");
        return; // TODO: Verify if it needs to return here
      }
      else
        context.references.insert(leftRef);
    }
    else // ref x ---
    {
      // TODO: Correct/Improve this error message
      context.errors.emplace_back("The nodename reference is not present on every side of the OR operator, resulting in an unresolved reference.");
      return; // TODO: Verify if it needs to return here
    }
  }

  for (auto *rightDef : rightDefinitions)
  {
    auto leftDefIt = leftDefinitions.find(rightDef);
    auto leftRefIt = leftReferences.find(rightDef);

    if (leftDefIt == leftDefinitions.end() && leftRefIt == leftReferences.end()) // --- x def
    {
      // TODO: Correct/Improve this error message
      context.errors.emplace_back("The nodename definition is not present on every side of the OR operator, so it will not be accessible outside the side where it is defined.");
      return; // TODO: Verify if it needs to return here
    }
  }

  for (auto *rightRef : rightReferences)
  {
    auto leftDefIt = leftDefinitions.find(rightRef);
    auto leftRefIt = leftReferences.find(rightRef);

    if (leftDefIt == leftDefinitions.end() && leftRefIt == leftReferences.end()) // --- x ref
    {
      // TODO: Correct/Improve this error message
      context.errors.emplace_back("The nodename reference is not present on every side of the OR operator, resulting in an unresolved reference.");
      return; // TODO: Verify if it needs to return here
    }
  }
}
