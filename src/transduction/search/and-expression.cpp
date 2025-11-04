#include "and-expression.hpp"
#include "nodename_info.hpp"

Transduction::Search::AndExpression::AndExpression(SearchExpression *leftExpression, SearchExpression *rightExpression)
  : SearchExpression(leftExpression->getDefinitions(), leftExpression->getReferences()), leftExpression(leftExpression), rightExpression(rightExpression)
{
  auto &leftDefinitions = leftExpression->getDefinitions();
  auto &leftReferences = leftExpression->getReferences();
  auto &rightDefinitions = rightExpression->getDefinitions();
  auto &rightReferences = rightExpression->getReferences();

  for (auto *rightDef : rightDefinitions)
  {
    bool definedBefore = leftDefinitions.find(rightDef) != leftDefinitions.end();
    bool referencedBefore = leftReferences.find(rightDef) == leftReferences.end();

    if (definedBefore)
      // TODO: Correct/Improve this error message
      // TODO: Create an exception for this
      throw "The nodename definition is already defined before.";
    else if (referencedBefore)
      // TODO: Correct/Improve this error message
      // TODO: Create an exception for this
      throw "The nodename definition is being referenced before.";
    else
      definitions.insert(rightDef);
  }

  for (auto *rightRef : rightReferences)
  {
    auto leftDefIt = leftDefinitions.find(rightRef);
    auto leftRefIt = leftReferences.find(rightRef);
    
    bool isDefinedBefore = leftDefIt != leftDefinitions.end();
    bool isDefinedBeforeWithDifferentPlaceholder = isDefinedBefore
      && (*leftDefIt)->placeholder != rightRef->placeholder;
    bool isReferencedBeforeWithDifferentPlaceholder = leftRefIt != leftReferences.end()
      && (*leftRefIt)->placeholder != rightRef->placeholder;

    if (isDefinedBeforeWithDifferentPlaceholder)
      // TODO: Correct/Improve this error message
      // TODO: Create an exception for this
      throw "The nodename reference is defined before, but with a different placeholder type.";
    else if (isReferencedBeforeWithDifferentPlaceholder)
      // TODO: Correct/Improve this error message
      // TODO: Create an exception for this
      throw "The nodename reference is referenced before, but with a different placeholder type.";
    else if (!isDefinedBefore)
      references.insert(rightRef);
  }
}

Transduction::Search::AndExpression::~AndExpression()
{
  delete leftExpression;
  delete rightExpression;
}
  
bool Transduction::Search::AndExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  symbolTable.enterScope();

  bool matched = leftExpression->match(tree, symbolTable)
    && rightExpression->match(tree, symbolTable);

  if (matched)
    return true;
  
  symbolTable.exitScope();
  return false;
}
