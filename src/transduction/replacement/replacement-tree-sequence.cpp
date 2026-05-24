#include "replacement-tree.hpp"
#include "replacement-tree-sequence.hpp"

Transduction::Replacement::ReplacementTreeSequence::ReplacementTreeSequence(
  std::vector<ReplacementTree*> &replacementTrees) : replacementTrees(replacementTrees) {}

  Transduction::Replacement::ReplacementTreeSequence::ReplacementTreeSequence(
  std::initializer_list<ReplacementTree*> replacementTrees) : replacementTrees(replacementTrees) {}

Transduction::Replacement::ReplacementTreeSequence::~ReplacementTreeSequence()
{
  for (auto replacementTree: replacementTrees)
    delete replacementTree;
}

void Transduction::Replacement::ReplacementTreeSequence::addTree(ReplacementTree *tree)
{
  replacementTrees.push_back(tree);
}

std::vector<Transduction::Replacement::ReplacementTree*>::iterator
Transduction::Replacement::ReplacementTreeSequence::begin()
{
  return replacementTrees.begin();
}

std::vector<Transduction::Replacement::ReplacementTree*>::iterator
Transduction::Replacement::ReplacementTreeSequence::end()
{
  return replacementTrees.end();
}

bool Transduction::Replacement::ReplacementTreeSequence::empty() const
{
  return replacementTrees.empty();
}

std::vector<Transduction::SyntaxTree*>
Transduction::Replacement::ReplacementTreeSequence::generateSyntaxTrees(
  const std::map<unsigned int, Transduction::NodenameMatch> &matches) const
{
  std::vector<Transduction::SyntaxTree*> result;

  for (auto replacementTree : replacementTrees)
  {
    auto generatedSyntaxTrees = replacementTree->generateSyntaxTrees(matches);
    result.insert(result.end(), generatedSyntaxTrees.begin(), generatedSyntaxTrees.end());
  }

  return result;
}
