#include <exception>
#include <iostream>
#include <regex>
#include <sstream>
#include "nodename-info.hpp"
#include "nodename-machine.hpp"
#include "parsing-rules.hpp"
#include "placeholder.hpp"
#include "restriction-expression-factory.hpp"
#include "replacement-validation-context.hpp"
#include "search-validation-context.hpp"

Transduction::Search::NodenameExpression* Parsing::parseNodename(std::string &lexem)
{
  std::istringstream input(lexem);
  auto nodenameInfo = Nodename::NodenameMachine(input).run();
  return new Transduction::Search::NodenameExpression(nodenameInfo);
}

Transduction::Search::NodenameExpression* Parsing::parseEndMarker()
{
  return new Transduction::Search::NodenameExpression(Nodename::NodenameInfo::createEndMarkerInstance());
}

Transduction::Search::NodenameExpression* Parsing::parseSubtreeRange(std::string &lexem)
{
  auto placeholder = lexem[0] == '['
    ? Nodename::Placeholder::CUT
    : Nodename::Placeholder::COPY;
  int placeholderNumber = 0;

  size_t colonPos = lexem.find(':', 1);
  if (colonPos != string::npos)
    placeholderNumber = stoi(lexem.substr(1, colonPos - 1));

  return new Transduction::Search::NodenameExpression(Nodename::NodenameInfo::createSubtreeRangeInstance(placeholder, placeholderNumber));
}

Transduction::Replacement::ReplacementTree* Parsing::parseReplacementNode(const std::string &lexem)
{
  istringstream input(lexem);
  auto nodenameInfo = Nodename::NodenameMachine(input).run();

  if (!nodenameInfo->freeOfContext)
    // TODO: Correct/Improve this error message
    // TODO: Create an exception for this
    throw "Nodenames in replacement expression cannot have left or right contexts."; 
  if (nodenameInfo->undetermined)
    // TODO: Correct/Improve this error message
    // TODO: Create an exception for this
    throw "Nodenames in replacement expression cannot contain ANY, WILDCARD or REGEX.";

  std::string tag;
  if (nodenameInfo->defOrRef == Nodename::DefOrRef::NONE)
    tag = lexem;
  else
  {
    std::smatch matches;
    std::regex extractTagRegex(R"([\[\{](?:\d+:)?([^\]\}\s]*)[\]\}])");
    if (!std::regex_match(lexem, matches, extractTagRegex))
      throw "The given tag is invalid.";
    tag = matches[1].str();
  }

  auto placeholder = nodenameInfo->placeholder;
  auto placeholderNumber = nodenameInfo->placeholderNumber;
  delete nodenameInfo;
  return new Transduction::Replacement::ReplacementTree(tag, placeholder, placeholderNumber);
}

Transduction::Replacement::ReplacementTree* Parsing::parseReplacementTree(
  Transduction::Replacement::ReplacementTree *root,
  Transduction::Replacement::ReplacementTreeSequence *children)
{
  if (root->getPlaceholder() != Nodename::Placeholder::NONE)
    // TODO: Correct/Improve this error message
    // TODO: Create an exception for this
    throw "The tree root in replacement expression cannot have a placeholder.";

  root->setChildren(children);

  return new Transduction::Replacement::ReplacementTree(root->getTag(), children);
}

Transduction::Replacement::ReplacementTreeSequence*
Parsing::parseReplacementTreeSequence(
  Transduction::Replacement::ReplacementTreeSequence *treeSequence,
  Transduction::Replacement::ReplacementTree *tree)
{
  treeSequence->addTree(tree);
  return treeSequence;
}

Transduction::TransductionRule* Parsing::parseTransduction(
  Transduction::Search::SearchExpression *searchExpression,
  Transduction::Replacement::ReplacementExpression *replacementExpression)
{
  if (!searchExpression)
    // TODO: Correct/Improve this message error
    // TODO: Create an exception for this
    throw "Empty search expression.";

  if (!replacementExpression)
    // TODO: Correct/Improve this message error
    // TODO: Create an exception for this
    throw "Empty replacement expression.";

  Transduction::Search::Contexts::SearchValidationContext searchContext;
  searchExpression->print(); // TODO: remove it later
  searchExpression->validate(searchContext);

  if (!searchContext.warnings.empty())
  {
    for (auto w : searchContext.warnings)
      std::clog << "[WARNING] " << std::endl;
  }
  
  if (!searchContext.errors.empty())
  {
    std::ostringstream errors;
    errors << "Errors occurred in search expression." << std::endl;
    for (auto e: searchContext.errors)
      errors << "\t[ERROR] " << e << std::endl;
    throw std::runtime_error(errors.str());
  }

  auto &definitions = searchContext.definitions;
  auto &references = searchContext.references;

  // Check if all references are defined
  if (!references.empty())
    // TODO: Correct/Improve this message error
    // TODO: Create an exception for this
    throw "There are references that are not defined in search expression.";

  // Check if the main placeholder is defined
  auto it = definitions.find(Nodename::NodenameInfo::MAIN_PLACEHOLDER_NUMBER);
  if (it == definitions.end()
    || it->second->placeholder != Nodename::Placeholder::CUT
    || it->second->defOrRef != Nodename::DefOrRef::DEFINITION)
  {
    // TODO: Correct/Improve this message error
    // TODO: Create an exception for this
    throw "The search expression needs to have a definition to main placeholder.";
  }

  Transduction::Replacement::Contexts::ReplacementValidationContext replacementContext(searchContext.definitions);
  replacementExpression->validate(replacementContext);

  // TODO: if replacement expression is a treesequence then search expression cannot match with syntax tree root

  return new Transduction::TransductionRule(searchExpression, replacementExpression);
}