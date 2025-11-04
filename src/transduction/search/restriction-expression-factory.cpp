#include <regex>
#include "has-leftmost-descendant-as-expression.hpp"
#include "has-nth-child-as-expression.hpp"
#include "has-nth-to-last-child-as-expression.hpp"
#include "has-rightmost-descendant-as-expression.hpp"
#include "has-unique-child-as-expression.hpp"
#include "has-unique-path-from-expression.hpp"
#include "has-unique-path-to-expression.hpp"
#include "is-ancestor-of-expression.hpp"
#include "is-child-of-expression.hpp"
#include "is-descendant-of-expression.hpp"
#include "is-equal-to-expression.hpp"
#include "is-immediately-left-sibling-of-expression.hpp"
#include "is-immediately-right-sibling-of-expression.hpp"
#include "is-left-sibling-of-expression.hpp"
#include "is-leftmost-descendant-of-expression.hpp"
#include "is-nth-child-of-expression.hpp"
#include "is-nth-to-last-child-of-expression.hpp"
#include "is-parent-of-expression.hpp"
#include "is-right-sibling-of-expression.hpp"
#include "is-rightmost-descendant-of-expression.hpp"
#include "is-sibling-of-expression.hpp"
#include "is-unique-child-of-expression.hpp"
#include "restriction-expression-factory.hpp"

Transduction::Search::SearchExpression*
Transduction::Search::RestrictionExpressionFactory::create(
  const std::string &operation,
  Transduction::Search::SearchExpression *expression)
{
  if (operation == "<")
    return new Transduction::Search::IsParentOfExpression(expression);

  if (operation == ">")
    return new Transduction::Search::IsChildOfExpression(expression);

  if (operation == "<,")
    return new Transduction::Search::HasNthChildAsExpression(1u, expression);

  if (operation == ">,")
    return new Transduction::Search::IsNthChildOfExpression(1u, expression);

  if (operation == "<-" || operation == "<'")
    return new Transduction::Search::HasNthToLastChildAsExpression(1u, expression);

  if (operation == ">-" || operation == ">'")
    return new Transduction::Search::IsNthChildOfExpression(1u, expression);

  if (operation == "<:")
    return new Transduction::Search::HasUniqueChildAsExpression(expression);

  if (operation == ">:")
    return new Transduction::Search::IsUniqueChildOfExpression(expression);

  if (operation == "<<")
    return new Transduction::Search::IsAncestorOfExpression(expression);
  
  if (operation == ">>")
    return new Transduction::Search::IsDescendantOfExpression(expression);
  
  if (operation == "<<,")
    return new Transduction::Search::HasLeftmostDescendantAsExpression(expression);
  
  if (operation == ">>,")
    return new Transduction::Search::IsLeftmostDescendantOfExpression(expression);

  if (operation == "<<'")
    return new Transduction::Search::HasRightmostDescendantAsExpression(expression);
  
  if (operation == ">>'")
    return new Transduction::Search::IsRightmostDescendantOfExpression(expression);

  if (operation == "<<:")
    return new Transduction::Search::HasUniquePathToExpression(expression);

  if (operation == ">>:")
    return new Transduction::Search::HasUniquePathFromExpression(expression);

  if (operation == "$")
    return new Transduction::Search::IsSiblingOfExpression(expression);

  if (operation == "$.")
    return new Transduction::Search::IsImmediatelyLeftSiblingOfExpression(expression);

  if (operation == "$,")
    return new Transduction::Search::IsImmediatelyRightSiblingOfExpression(expression);
  
  if (operation == "$..")
    return new Transduction::Search::IsLeftSiblingOfExpression(expression);

  if (operation == "$,,")
    return new Transduction::Search::IsRightSiblingOfExpression(expression);

  if (operation == "=")
    return new Transduction::Search::IsEqualToExpression(expression);

  std::regex numberedOperationPattern("^([<>]-?)([1-9][0-9]*)$");
  std::smatch matches;
  
  if (std::regex_match(operation, matches, numberedOperationPattern))
  {
    auto op = matches[1].str();
    auto numberStr = matches[2].str();

    unsigned long number = std::stoul(numberStr);
    if (number > UINT_MAX)
      throw "The operator \"" + operation + "\" has a number out of range.";

    if (op == "<")
      return new Transduction::Search::HasNthChildAsExpression((unsigned int) number, expression);

    if (op == ">")
      return new Transduction::Search::IsNthChildOfExpression((unsigned int) number, expression);

    if (op == "<-")
      return new Transduction::Search::HasNthToLastChildAsExpression((unsigned int) number, expression);

    if (op == ">-")
      return new Transduction::Search::IsNthToLastChildOfExpression((unsigned int) number, expression);
  }

  // TODO: Correct/Improve this message
  // TODO: Create an exception for this
  throw "Invalid restriction! The given operator does not represent a valid operation.";
}