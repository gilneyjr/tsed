#include <regex>
#include <sstream>
#include "nodename-info.hpp"
#include "nodename-machine.hpp"
#include "parsing-rules.hpp"
#include "placeholder.hpp"
#include "replacement-internal-node.hpp"
#include "replacement-leaf-node.hpp"
#include "restriction-expression-factory.hpp"
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

Transduction::Replacement::ReplacementLeafNode* Parsing::parseReplacementNode(const std::string &lexem, const Nodename::NodenameInfoSet &searchExpressionDefinitions)
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
  
  if (nodenameInfo->placeholder != Nodename::Placeholder::NONE)
  {
    auto it = searchExpressionDefinitions.find(nodenameInfo);
    if (it == searchExpressionDefinitions.end())
      // TODO: Correct/Improve this error message
      // TODO: Create an exception for this
      throw "The placeholder is not defined in the search expression.";
    if ((*it)->placeholder != nodenameInfo->placeholder)
      // TODO: Correct/Improve this error message
      // TODO: Create an exception for this
      throw "The placeholder has a different type of its definition in the search expression.";
  }

  // TODO: check if this extraction is correct
  std::smatch matches;
  std::regex extractTagRegex(R"([\[\{]\s*(?:\d+\s*:\s*)?([^\]\}]*)\s*[\]\}])");
  if (!std::regex_match(lexem, matches, extractTagRegex))
    throw "The given tag is invalid.";
  
  auto tag = matches[1].str();
  auto placeholder = nodenameInfo->placeholder;
  auto placeholderNumber = nodenameInfo->placeholderNumber;
  delete nodenameInfo;
  return new Transduction::Replacement::ReplacementLeafNode(tag, placeholder, placeholderNumber);
}

Transduction::Replacement::ReplacementTree* Parsing::parseReplacementTree(Transduction::Replacement::ReplacementLeafNode *root, Transduction::Replacement::TreeSequence *children)
{
  if (root->getPlaceholder() != Nodename::Placeholder::NONE)
    // TODO: Correct/Improve this error message
    // TODO: Create an exception for this
    throw "The tree root in replacement expression cannot have a placeholder.";

  return new Transduction::Replacement::ReplacementInternalNode(root->getTag(), children);
}

Transduction::Replacement::TreeSequence* Parsing::parseReplacementTreeSequence(
  Transduction::Replacement::TreeSequence *treeSequence,
  Transduction::Replacement::ReplacementTree *tree)
{
  treeSequence->push_back(tree);
  return treeSequence;
}

Transduction::TransductionRule* Parsing::parseTransduction(
  Transduction::Search::SearchExpression *searchExpression,
  Transduction::Replacement::TreeSequence *replacementExpression)
{
  if (!searchExpression)
    // TODO: Correct/Improve this message error
    // TODO: Create an exception for this
    throw "Empty search expression.";

  if (!replacementExpression)
    // TODO: Correct/Improve this message error
    // TODO: Create an exception for this
    throw "Empty replacement expression.";

  Transduction::Search::Contexts::SearchValidationContext searchExpressionValidationContext;
  searchExpression->validate(searchExpressionValidationContext);

  auto &definitions = searchExpressionValidationContext.definitions;
  auto &references = searchExpressionValidationContext.references;

  // Check if all references are defined
  if (!references.empty())
    // TODO: Correct/Improve this message error
    // TODO: Create an exception for this
    throw "There are references that are not defined in search expression.";

  // Check if the main placeholder is defined
  Nodename::NodenameInfo nodenameWithPlaceholderNumber0;
  nodenameWithPlaceholderNumber0.placeholderNumber = 0;
  auto it = definitions.find(&nodenameWithPlaceholderNumber0);
  if (it == definitions.end() || (*it)->placeholder != Nodename::Placeholder::CUT || (*it)->defOrRef != Nodename::DefOrRef::DEFINITION)
    // TODO: Correct/Improve this message error
    // TODO: Create an exception for this
    throw "The search expression needs to have a definition to main placeholder.";

  // TODO: Think if it is necessary to check the replacement expression's references are defined on search expression

  return new Transduction::TransductionRule(searchExpression, replacementExpression);
}