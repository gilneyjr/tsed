#include "nodename-info.hpp"
#include "or-expression.hpp"

Transduction::Search::OrExpression::OrExpression(SearchExpression *leftExpression, SearchExpression *rightExpression)
  : leftExpression(leftExpression), rightExpression(rightExpression)  
{
  auto &leftDefinitions = leftExpression->getDefinitions();
  auto &leftReferences = leftExpression->getReferences();
  auto &rightDefinitions = rightExpression->getDefinitions();
  auto &rightReferences = rightExpression->getReferences();

  for (auto *leftDef : leftDefinitions)
  {
    auto rightDefIt = rightDefinitions.find(leftDef);
    auto rightRefIt = rightReferences.find(leftDef);

    if (rightDefIt != rightDefinitions.end()) // def x def
    {
      if (leftDef->placeholder != (*rightDefIt)->placeholder)
        // TODO: Correct/Improve this error message
        // TODO: Create an exception for this
        throw "The nodename definition must have the same placeholder type in every sides of the OR operator.";
      else
        definitions.insert(leftDef);
    } 
    else if (rightRefIt != rightReferences.end()) // def x ref
      // TODO: Correct/Improve this error message
      // TODO: Create an exception for this
      throw "The node name reference is not being defined on the side of the OR operator where it is used.";
    else // def x ---
      // TODO: Correct/Improve this error message
      // TODO: Create an exception for this
      // TODO: Think how to pass this above without throw an exception
      throw "The nodename definition is not present on every side of the OR operator, so it will not be accessible outside the side where it is defined.";
  }

  for (auto *leftRef : leftReferences)
  {
    auto rightDefIt = rightDefinitions.find(leftRef);
    auto rightRefIt = rightReferences.find(leftRef);

    if (rightDefIt != rightDefinitions.end()) // ref x def
      // TODO: Correct/Improve this error message
      // TODO: Create an exception for this
      throw "The node name reference is not being defined on the side of the OR operator where it is used.";
    else if (rightRefIt != rightReferences.end()) // ref x ref
    {
      if (leftRef->placeholder != (*rightRefIt)->placeholder)
        // TODO: Correct/Improve this error message
        // TODO: Create an exception for this
        throw "The nodename reference must have the same placeholder type in every sides of the OR operator.";
      else
        references.insert(leftRef);
    }
    else // ref x ---
      // TODO: Correct/Improve this error message
      // TODO: Create an exception for this
      throw "The nodename reference is not present on every side of the OR operator, resulting in an unresolved reference.";
  }

  for (auto *rightDef : rightDefinitions)
  {
    auto leftDefIt = leftDefinitions.find(rightDef);
    auto leftRefIt = leftReferences.find(rightDef);

    if (leftDefIt == leftDefinitions.end() && leftRefIt == leftReferences.end()) // --- x def
      // TODO: Correct/Improve this error message
      // TODO: Create an exception for this
      throw "The nodename definition is not present on every side of the OR operator, so it will not be accessible outside the side where it is defined.";
  }

  for (auto *rightRef : rightReferences)
  {
    auto leftDefIt = leftDefinitions.find(rightRef);
    auto leftRefIt = leftReferences.find(rightRef);

    if (leftDefIt == leftDefinitions.end() && leftRefIt == leftReferences.end()) // --- x ref
      // TODO: Correct/Improve this error message
      // TODO: Create an exception for this
      throw "The nodename reference is not present on every side of the OR operator, resulting in an unresolved reference.";
  }
}

Transduction::Search::OrExpression::~OrExpression()
{
  delete leftExpression;
  delete rightExpression;
}
  
bool Transduction::Search::OrExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  symbolTable.enterScope();
  
  bool matched = leftExpression->match(tree, symbolTable)
    || rightExpression->match(tree, symbolTable);

  if (matched)
    return true;

  symbolTable.exitScope();
  return false;
}
