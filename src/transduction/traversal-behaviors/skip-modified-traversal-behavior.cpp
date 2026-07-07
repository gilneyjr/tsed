#include "skip-modified-traversal-behavior.hpp"

Transduction::SkipModifiedTraversalBehavior::SkipModifiedTraversalBehavior(
  SyntaxTreeIteratorStrategy *iteratorStrategy
) : TraversalBehavior(iteratorStrategy) {}

void Transduction::SkipModifiedTraversalBehavior::start(SyntaxTree *tree)
{
  modified.clear();
  TraversalBehavior::start(tree);
}

void Transduction::SkipModifiedTraversalBehavior::notifyMatch(const SymbolTable &symbolTable)
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

void Transduction::SkipModifiedTraversalBehavior::notifyReplacement(
  const std::vector<SyntaxTree*> &replacedTrees)
{
  // TODO: verify if I need to insert replaced trees' descendents
  modified.insert(replacedTrees.begin(), replacedTrees.end());
  while (hasNext() && modified.find(&*_next) != modified.end())
    ++_next;
}