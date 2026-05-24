#include "nodename-match.hpp"

Transduction::NodenameMatch Transduction::NodenameMatch::clone() const
{
  NodenameMatch clonedMatch;

  clonedMatch.isRange = isRange;
  clonedMatch.left = left;
  clonedMatch.middle = middle;
  clonedMatch.right = right;
  clonedMatch.placeholder = placeholder;

  for(const auto* tree : trees)
    clonedMatch.trees.push_back(tree->clone());

  return clonedMatch;
}

bool Transduction::NodenameMatch::matchedIsRoot()
{
  if (trees.size() != 1)
    return false;
  return trees.front()->getParent()->isEndMarker();
}