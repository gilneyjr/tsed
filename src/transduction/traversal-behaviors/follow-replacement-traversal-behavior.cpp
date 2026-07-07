#include "follow-replacement-traversal-behavior.hpp"
#include "nodename-info.hpp"

#include <algorithm>

Transduction::FollowReplacementTraversalBehavior::FollowReplacementTraversalBehavior(
  SyntaxTreeIteratorStrategy *iteratorStrategy,
  bool advanceReplacementRoot
) : Transduction::TraversalBehavior(iteratorStrategy)
  , advanceReplacementRoot(advanceReplacementRoot)
  , currentIsInMainPlaceholder(false) {}

void Transduction::FollowReplacementTraversalBehavior::notifyMatch(const SymbolTable &symbolTable)
{
  const auto cutMatchedSubtrees = getCutMatchedSubtrees(symbolTable);

  auto mainPlaceholderTrees = symbolTable
    .lookup(Nodename::NodenameInfo::MAIN_PLACEHOLDER_NUMBER)
    .second
    .trees;
  currentIsInMainPlaceholder = std::find(
    mainPlaceholderTrees.begin(),
    mainPlaceholderTrees.end(),
    &*_current
  ) != mainPlaceholderTrees.end();

  while (hasNext())
  {
    SyntaxTree* topmostCutSubtreeInAncestry = getTopmostCutSubtreeInAncestry(cutMatchedSubtrees);
    bool willNextBeKept = topmostCutSubtreeInAncestry == nullptr;
    if (willNextBeKept)
      break;
    advanceNextPastSubtree(topmostCutSubtreeInAncestry);
  }
}

void Transduction::FollowReplacementTraversalBehavior::notifyReplacement(
  const std::vector<SyntaxTree*> &replacedTrees)
{
  if (!replacedTrees.empty())
  {
    if (iteratorStrategy->direction() == IteratorDirection::FORWARD)
      _next = createIterator(replacedTrees.front());
    else
      _next = createIterator(replacedTrees.back());

    if (currentIsInMainPlaceholder && advanceReplacementRoot)
      ++_next;
  }
}
