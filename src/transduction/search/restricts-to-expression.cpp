#include "def_or_ref.hpp"
#include "restricts-to-expression.hpp"

Transduction::Search::RestrictsToExpression::RestrictsToExpression(NodenameExpression *nodenameExpression, SearchExpression *restrictionsExpression)
  : SearchExpression(restrictionsExpression->getDefinitions(), restrictionsExpression->getReferences())
  , nodenameExpression(nodenameExpression), restrictionsExpression(restrictionsExpression)
{
  auto *nodenameInfo = nodenameExpression->getNodenameInfo();
  auto &restrictionsDefinitions = restrictionsExpression->getDefinitions();
  auto &restrictionsReferences = restrictionsExpression->getReferences();

  if (nodenameInfo->defOrRef == Nodename::DefOrRef::DEFINITION)
  {
    auto restrDefIt = restrictionsDefinitions.find(nodenameInfo);
    if (restrDefIt != restrictionsDefinitions.end())
      // TODO: Correct/Improve this error message
      // TODO: Create an exception for this
      throw "The nodename is already defined before.";
    
    auto restrRefIt = restrictionsReferences.find(nodenameInfo);
    if (restrRefIt != restrictionsReferences.end())
    {
      if (nodenameInfo->placeholder != (*restrRefIt)->placeholder)
        // TODO: Correct/Improve this error message
        // TODO: Create an exception for this
        throw "The nodename reference must have the same placeholder type as its definition.";
      references.erase(nodenameInfo); // Resolve the search primary reference referenced on restrictions
    }

    definitions.insert(nodenameInfo);
  }
  else if (nodenameInfo->defOrRef == Nodename::DefOrRef::REFERENCE)
  {
    auto restrDefIt = restrictionsDefinitions.find(nodenameInfo);
    if (restrDefIt != restrictionsDefinitions.end())
      // TODO: Correct/Improve this error message
      // TODO: Create an exception for this
      throw "The nodename is defined after its reference.";

    auto restrRefIt = restrictionsReferences.find(nodenameInfo);
    if (restrRefIt != restrictionsReferences.end())
    {
      if (nodenameInfo->placeholder != (*restrRefIt)->placeholder)
        // TODO: Correct/Improve this error message
        // TODO: Create an exception for this
        throw "The nodename reference must have the same placeholder type in all references.";
    }
    else
      references.insert(nodenameInfo);
  }
}

Transduction::Search::RestrictsToExpression::~RestrictsToExpression()
{
  delete nodenameExpression;
  delete restrictionsExpression;
}

bool Transduction::Search::RestrictsToExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  return nodenameExpression->match(tree, symbolTable)
    && restrictionsExpression->match(tree, symbolTable);
}
