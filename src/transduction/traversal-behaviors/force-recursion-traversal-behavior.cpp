#include "force-recursion-traversal-behavior.hpp"
#include "nodename-info.hpp"

#include <algorithm>

Transduction::ForceRecursionTraversalBehavior::ForceRecursionTraversalBehavior(
  SyntaxTreeIteratorStrategy *iteratorStrategy
) : Transduction::TraversalBehavior(iteratorStrategy), nextIsMainPlaceholder(false) {}

std::set<Transduction::SyntaxTree*>
Transduction::ForceRecursionTraversalBehavior::getCutMatchedSubtrees(
  const SymbolTable &symbolTable)
{
  std::set<SyntaxTree*> subtrees;
  for (const auto &[_, match] : symbolTable.getAllMatches())
    if (match.placeholder == Nodename::Placeholder::CUT)
      subtrees.insert(match.trees.cbegin(), match.trees.cend());
  return subtrees;
}

Transduction::SyntaxTree*
Transduction::ForceRecursionTraversalBehavior::getTopmostCutSubtreeInAncestry(
  const std::set<SyntaxTree*> &cutPlaceholderSubtrees)
{
  SyntaxTree *topmostCutSubtreeInAncestry = nullptr;
  for (auto subtree = &*_next; subtree != nullptr && !subtree->isEndMarker(); subtree = subtree->getParent())
  {
    if (cutPlaceholderSubtrees.find(subtree) != cutPlaceholderSubtrees.end())
      topmostCutSubtreeInAncestry = subtree;
  }
  return topmostCutSubtreeInAncestry;
}

void Transduction::ForceRecursionTraversalBehavior::advanceNextPastSubtree(SyntaxTree *subtree)
{
  _next = createIterator(subtree);

  while (hasNext())
  {
    bool isInsideSubtree = false;
    for (SyntaxTree* node = &*_next; node != nullptr; node = node->getParent())
    {
      if (node == subtree)
      {
        isInsideSubtree = true;
        break;
      }
    }

    if (!isInsideSubtree)
      break;
    ++_next;
  }
}

void Transduction::ForceRecursionTraversalBehavior::notifyMatch(const SymbolTable &symbolTable)
{
  nextIsMainPlaceholder = false;

  const auto cutMatchedSubtrees = getCutMatchedSubtrees(symbolTable);
  while (hasNext())
  {
    SyntaxTree* topmostCutSubtreeInAncestry = getTopmostCutSubtreeInAncestry(cutMatchedSubtrees);
    bool willNextBeKept = topmostCutSubtreeInAncestry == nullptr;
    if (willNextBeKept)
      break;

    const NodenameMatch &mainPlaceholder = symbolTable.lookup(Nodename::NodenameInfo::MAIN_PLACEHOLDER_NUMBER).second;
    bool topmostIsInMainPlaceholder = std::find(
      mainPlaceholder.trees.begin(),
      mainPlaceholder.trees.end(),
      topmostCutSubtreeInAncestry
    ) != mainPlaceholder.trees.end();

    if (topmostIsInMainPlaceholder)
    {
      nextIsMainPlaceholder = true;
      break;
    }

    advanceNextPastSubtree(topmostCutSubtreeInAncestry);
  }
}

void Transduction::ForceRecursionTraversalBehavior::notifyReplacement(
  const std::vector<SyntaxTree*> &replacedTrees)
{
  // TODO: think what do if replacedTrees is empty
  if (nextIsMainPlaceholder)
  {
    if (iteratorStrategy->direction() == IteratorDirection::FORWARD)
      _next = createIterator(replacedTrees.front());
    else
      _next = createIterator(replacedTrees.back());
  }
  nextIsMainPlaceholder = false;
}
