#include "and-expression.hpp"

Transduction::Search::AndExpression::AndExpression(OperationExpression *leftExpression, OperationExpression *rightExpression)
  : leftExpression(leftExpression), rightExpression(rightExpression) {}

Transduction::Search::AndExpression::~AndExpression()
{
  if (leftExpression)
    delete leftExpression;
  if (rightExpression)
    delete rightExpression;
}

bool Transduction::Search::AndExpression::match(Transduction::Search::Contexts::SearchMatchContext &context) const
{
  context.symbolTable->enterScope();

  bool matched = leftExpression->match(context)
    && rightExpression->match(context);

  if (matched)
    return true;
  
  context.symbolTable->exitScope();
  return false;
}

void Transduction::Search::AndExpression::validate(Contexts::SearchValidationContext &context) const
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
  rightContext.leftIsEndMarker = context.leftIsEndMarker;

  leftExpression->validate(leftContext);
  rightExpression->validate(rightContext);
  context.errors.insert(context.errors.end(), rightContext.errors.begin(), rightContext.errors.end());
  context.warnings.insert(context.warnings.end(), rightContext.warnings.begin(), rightContext.warnings.end());

  if (leftContext.errors.size() > 0 || rightContext.errors.size() > 0)
    return;

  auto &leftDefinitions = leftContext.definitions;
  auto &leftReferences = leftContext.references;
  auto &rightDefinitions = rightContext.definitions;
  auto &rightReferences = rightContext.references;

  for (auto [rightDefKey, rightDef] : rightDefinitions)
  {
    bool definedBefore = leftDefinitions.find(rightDefKey) != leftDefinitions.end();
    bool referencedBefore = leftReferences.find(rightDefKey) == leftReferences.end();

    if (definedBefore)
    {
      // TODO: Correct/Improve this error message
      context.errors.emplace_back("The nodename definition is already defined before.");
      return; // TODO: Verify if it needs to return here
    }
    else if (referencedBefore)
    {
      // TODO: Correct/Improve this error message
      context.errors.emplace_back("The nodename definition is being referenced before its definition.");
      return; // TODO: Verify if it needs to return here
    }
    else
      context.definitions.insert({rightDefKey, rightDef});
  }

  for (auto [rightRefKey, rightRef] : rightReferences)
  {
    auto leftDefIt = leftDefinitions.find(rightRefKey);
    auto leftRefIt = leftReferences.find(rightRefKey);
    
    bool isDefinedBefore = leftDefIt != leftDefinitions.end();
    bool isDefinedBeforeWithDifferentPlaceholder = isDefinedBefore
      && leftDefIt->second->placeholder != rightRef->placeholder;
    bool isReferencedBeforeWithDifferentPlaceholder = leftRefIt != leftReferences.end()
      && leftRefIt->second->placeholder != rightRef->placeholder;

    if (isDefinedBeforeWithDifferentPlaceholder)
    {
      // TODO: Correct/Improve this error message
      context.errors.emplace_back("The nodename reference is defined before, but with a different placeholder type.");
      return; // TODO: Verify if it needs to return here
    }
    else if (isReferencedBeforeWithDifferentPlaceholder)
    {
      // TODO: Correct/Improve this error message
      context.errors.emplace_back("The nodename reference is referenced before, but with a different placeholder type.");
      return; // TODO: Verify if it needs to return here
    }
    else if (!isDefinedBefore)
      context.references.insert({rightRefKey, rightRef});
  }
}
