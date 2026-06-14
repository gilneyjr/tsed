#include "follow-replacement-traversal-behavior.hpp"
#include "nodename-info.hpp"

Transduction::FollowReplacementTraversalBehavior::FollowReplacementTraversalBehavior(
  SyntaxTreeIteratorStrategy *iteratorStrategy
) : TraversalBehavior(iteratorStrategy) {}

void Transduction::FollowReplacementTraversalBehavior::notifyMatch(const SymbolTable &symbolTable)
{
  const auto cutMatchedSubtrees = getCutMatchedSubtrees(symbolTable);
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
    ++_next;
  }
}
