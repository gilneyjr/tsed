#include <regex>
#include "nodename-expression.hpp"
#include "nodename-match.hpp"

Transduction::Search::NodenameExpression::NodenameExpression(Nodename::NodenameInfo *nodenameInfo)
  : nodenameInfo(nodenameInfo) {}

Transduction::Search::NodenameExpression::~NodenameExpression()
{
  if (nodenameInfo)
    delete nodenameInfo;
}

bool Transduction::Search::NodenameExpression::isEndMarker() const
{
  return nodenameInfo != nullptr && nodenameInfo->type == Nodename::NodenameInfoType::END_MARKER;
}

bool Transduction::Search::NodenameExpression::match(Contexts::SearchMatchContext &context) const
{
  if (context.current == nullptr) 
    return false; // TODO: check what it needs to be done here

  bool currentIsEndMarker = context.current->isEndMarker();
  bool nodenameIsEndMarker = nodenameInfo->type == Nodename::NodenameInfoType::END_MARKER;
  if (currentIsEndMarker || nodenameIsEndMarker)
  {
    if (!currentIsEndMarker || !nodenameIsEndMarker)
      return false;

    // Check if end marker is operating with another end marker. Ex: # < #
    if (context.matchedIsEndMarker)
      return false; // TODO: Should it throw an error? Decide it!

    return true;
  }

  if (nodenameInfo->defOrRef == Nodename::DefOrRef::REFERENCE)
  {
    auto result = context.symbolTable->lookup(nodenameInfo->placeholderNumber);
    if (!result.first)
      return false;
    return context.current == result.second.tree;
  }

  std::regex pattern("^" + nodenameInfo->regex + "$");
  std::smatch matches;

  if (!std::regex_match(context.current->getTag(), matches, pattern))
    return false;

  if (nodenameInfo->placeholder != Nodename::Placeholder::NONE)
  {
    Transduction::NodenameMatch match;
    match.left = matches[1];
    match.middle = matches[2];
    match.right = matches[3];
    match.tree = context.current;
    match.placeholder = nodenameInfo->placeholder;
    context.symbolTable->insert(nodenameInfo->placeholderNumber, match);
  }
  
  return true;
}

void Transduction::Search::NodenameExpression::validate(Contexts::SearchValidationContext &context) const
{
  if (!nodenameInfo)
  {
    context.errors.emplace_back("Malformed search expression: a nodename expression must have a nodename information in order to match nodes in the syntax tree search.");
    return;
  }

  if (nodenameInfo->defOrRef == Nodename::DefOrRef::DEFINITION)
    context.definitions.insert({nodenameInfo->placeholderNumber, nodenameInfo});
  else if (nodenameInfo->defOrRef == Nodename::DefOrRef::REFERENCE)
    context.references.insert({nodenameInfo->placeholderNumber, nodenameInfo});
}

// TODO: Remove it later
#include <iostream>
void Transduction::Search::NodenameExpression::print(int tab)
{
  for (int i = 1; i <= tab; i++)
    std::cout << "  ";
  if (nodenameInfo->type == Nodename::NodenameInfoType::END_MARKER)
    std::cout << "#" << std::endl;
  else
    std::cout << "\"" << nodenameInfo->regex << "\"" << std::endl;
}