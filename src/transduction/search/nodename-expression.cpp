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
  if (!context.matched)
    return context.matchedIsEndMarker && nodenameInfo->type == Nodename::NodenameInfoType::END_MARKER;

  if (nodenameInfo->defOrRef == Nodename::DefOrRef::REFERENCE)
  {
    auto result = context.symbolTable->lookup(nodenameInfo->placeholderNumber);
    if (!result.first)
      return false;
    return context.matched == result.second.tree;
  }

  std::regex pattern("^" + nodenameInfo->regex + "$");
  std::smatch matches;

  if (std::regex_match(context.matched->getTag(), matches, pattern))
  {
    if (nodenameInfo->placeholder != Nodename::Placeholder::NONE)
    {
      Transduction::NodenameMatch match;
      match.left = matches[1];
      match.middle = matches[2];
      match.right = matches[3];
      match.tree = context.matched;
      match.placeholder = nodenameInfo->placeholder;
      context.symbolTable->insert(nodenameInfo->placeholderNumber, match);
    }
    
    return true;
  }

  return false;
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
