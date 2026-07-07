#include "force-recursion-traversal-behavior.hpp"
#include "nodename-info.hpp"

#include <algorithm>

Transduction::ForceRecursionTraversalBehavior::ForceRecursionTraversalBehavior(
  SyntaxTreeIteratorStrategy *iteratorStrategy,
  bool advanceReplacementRoot
) : Transduction::TraversalBehavior(iteratorStrategy)
  , nextIsMainPlaceholder(false)
  , advanceReplacementRoot(advanceReplacementRoot)
  , currentIsInMainPlaceholder(false) {}

void Transduction::ForceRecursionTraversalBehavior::notifyMatch(const SymbolTable &symbolTable)
{
  nextIsMainPlaceholder = false;

  const auto cutMatchedSubtrees = getCutMatchedSubtrees(symbolTable);
  const NodenameMatch &mainPlaceholder = symbolTable.lookup(Nodename::NodenameInfo::MAIN_PLACEHOLDER_NUMBER).second;
  
  currentIsInMainPlaceholder = std::find(
    mainPlaceholder.trees.begin(),
    mainPlaceholder.trees.end(),
    &*_current
  ) != mainPlaceholder.trees.end();

  while (hasNext())
  {
    SyntaxTree* topmostCutSubtreeInAncestry = getTopmostCutSubtreeInAncestry(cutMatchedSubtrees);
    bool willNextBeKept = topmostCutSubtreeInAncestry == nullptr;
    if (willNextBeKept)
      break;

    bool topmostIsInMainPlaceholder = std::find(
      mainPlaceholder.trees.begin(),
      mainPlaceholder.trees.end(),
      topmostCutSubtreeInAncestry
    ) != mainPlaceholder.trees.end();

    if (topmostIsInMainPlaceholder)
      nextIsMainPlaceholder = true;

    advanceNextPastSubtree(topmostCutSubtreeInAncestry);
  }
}

void Transduction::ForceRecursionTraversalBehavior::notifyReplacement(
  const std::vector<SyntaxTree*> &replacedTrees)
{
  if (nextIsMainPlaceholder && !replacedTrees.empty())
  {
    // TODO: create an method to get first

    if (iteratorStrategy->direction() == IteratorDirection::FORWARD)
      _next = createIterator(replacedTrees.front());
    else
      _next = createIterator(replacedTrees.back());
    
    if (currentIsInMainPlaceholder && replacedTrees.size() == 1 && advanceReplacementRoot)
      ++_next;
  }
  nextIsMainPlaceholder = false;
}
