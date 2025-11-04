#include <regex>
#include "nodename-expression.hpp"

Transduction::Search::NodenameExpression::NodenameExpression(Nodename::NodenameInfo *nodenameInfo)
  : nodenameInfo(nodenameInfo)
{
  if (nodenameInfo->defOrRef == Nodename::DefOrRef::DEFINITION)
    definitions.insert(nodenameInfo);
  else if (nodenameInfo->defOrRef == Nodename::DefOrRef::REFERENCE)
    references.insert(nodenameInfo);
}

bool Transduction::Search::NodenameExpression::match(SyntaxTree *tree, SymbolTable &symbolTable)
{
  if (nodenameInfo == nullptr)
    throw "Unexpected error occurred because nodename information was not parsed correctly."; // TODO: Correct/Improve this message

  if (tree == nullptr)
    return isEndMarker();

  if (nodenameInfo->defOrRef == Nodename::DefOrRef::REFERENCE)
  {
    auto result = symbolTable.lookup(nodenameInfo->placeholderNumber);
    if (!result.first)
      return false;
    return tree == result.second.tree;
  }

  std::regex pattern("^" + nodenameInfo->regex + "$");
  std::smatch matches;

  if (std::regex_match(tree->tag, matches, pattern))
  {
    if (nodenameInfo->placeholder != Nodename::Placeholder::NONE)
    {
      Transduction::NodenameMatch match;
      match.left = matches[1];
      match.middle = matches[2];
      match.right = matches[3];
      match.tree = tree;
      match.placeholder = nodenameInfo->placeholder;
      symbolTable.insert(nodenameInfo->placeholderNumber, match);
    }
    
    return true;
  }

  return false;
}

bool Transduction::Search::NodenameExpression::isEndMarker()
{
  return nodenameInfo->type == Nodename::NodenameInfoType::END_MARKER;
}

Nodename::NodenameInfo* Transduction::Search::NodenameExpression::getNodenameInfo()
{
  return nodenameInfo;
}