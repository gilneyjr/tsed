#include "replacement-expression.hpp"
#include "replacement-tree.hpp"
#include "symbol-table.hpp"

#include <iostream> // TODO: remove it and its uses later
#include <map> // TODO: verify if this include is necessary
#include <set> // TODO: verify if this include is necessary

Transduction::Replacement::ReplacementExpression::ReplacementExpression(
  ReplacementTreeSequence *treeSequence) : treeSequence(treeSequence) {}

Transduction::Replacement::ReplacementExpression::~ReplacementExpression()
{
  delete treeSequence;
}

std::vector<Transduction::SyntaxTree*>
Transduction::Replacement::ReplacementExpression::replace(
  Transduction::SyntaxTree *tree,
  Transduction::SymbolTable &symbolTable)
{
  // 1. Copy subtrees matched with placeholders
  auto matches = symbolTable.getAllMatches();
  auto clonedMatches = cloneMatches(matches);

  // 2. Set replacement point
  auto replacementPoint = markReplacementPoint(symbolTable);  

  // 3. Delete subtrees matched with cut placeholders from original tree
  deleteCutPlaceholdersFromTree(tree, replacementPoint, matches);

  // 4. Generate trees from replacement expression
  auto generatedTreesForReplacement = generateTreesForReplacement(clonedMatches);

  // 5. Replace replacement point with generated trees
  injectGeneratedTrees(replacementPoint, generatedTreesForReplacement);

  // 6. Delete Replacement Point
  if (replacementPoint != nullptr)
    delete replacementPoint;

  std::cout << "\tFinal tree:\n";
  std::cout << "\t" << *tree << std::endl;

  // TODO: verify if I need to delete this here
  // delete clonedMatches;

  return generatedTreesForReplacement;
}

std::map<unsigned int, Transduction::NodenameMatch>
Transduction::Replacement::ReplacementExpression::cloneMatches(
  const std::map<unsigned int, Transduction::NodenameMatch> &matches)
{
  std::cout << "> COPYING MATCHED SUBTREES\n";
  std::map<unsigned int, Transduction::NodenameMatch> clonedMatches;
  for (const auto& [key, match]: matches)
    clonedMatches.emplace(key, match.clone());
  return clonedMatches;
}

void Transduction::Replacement::ReplacementExpression::deleteCutPlaceholdersFromTree(
  SyntaxTree *tree,
  SyntaxTree *&replacementPoint,
  const std::map<unsigned int, NodenameMatch> &matches)
{
  std::cout << "> DELETING CUT PLACEHOLDERS' SUBTREES\n";
  std::cout << "Original tree:\n" << *tree << std::endl;

  std::map<unsigned int, std::set<SyntaxTree*>> subtreesToDeleteGroupedByDepth;

  for (auto &[key, match] : matches)
  {
    if (match.trees.empty() || match.placeholder != Nodename::Placeholder::CUT)
      continue;

    for (auto tree : match.trees)
    {
      auto depth = 0;
      auto work = tree->getParent();
      while (work != nullptr && !work->isEndMarker())
      {
        depth++;
        work = work->getParent();
      }
      subtreesToDeleteGroupedByDepth[depth].insert(tree);
    }
  }

  if (subtreesToDeleteGroupedByDepth.empty())
    std::cout << "INFO: There is no subtrees to delete.\n";

  for (auto it = subtreesToDeleteGroupedByDepth.rbegin(); it != subtreesToDeleteGroupedByDepth.rend(); ++it)
  {
    auto &[depth, subtrees] = *it;

    std::cout << "Depth " << depth << std::endl;
    if (subtrees.empty())
      std::cout << "\tINFO: There is no subtrees to delete on depth " << depth << ".\n";
    for (auto subtree : subtrees)
    {
      std::cout << "\tDeleting subtree: " << *subtree << std::endl;
      subtree->detachSubtree();

      if (replacementPoint != nullptr)
      {
        for (auto replacementPointAncestor = replacementPoint->getParent();
          replacementPointAncestor != nullptr;
          replacementPointAncestor = replacementPointAncestor->getParent())
        {
          if (replacementPointAncestor == subtree)
          {
            replacementPoint = nullptr;
            break;
          }
        }
      }

      delete subtree;
    }
  }

  std::cout << "Tree without cutted matches:\n" << *tree << std::endl;
}

std::vector<Transduction::SyntaxTree*>
Transduction::Replacement::ReplacementExpression::generateTreesForReplacement(
  const std::map<unsigned int, Transduction::NodenameMatch> &matches) const
{
  std::cout << "> GENERATING TREES FOR REPLACEMENT\n";
  auto generatedSyntaxTrees = treeSequence->generateSyntaxTrees(matches);
  
  std::cout << "\tGenerated Syntax Trees:\n";
  for (auto syntaxTree : generatedSyntaxTrees)
    std::cout << "\t\t" << *syntaxTree << std::endl;
  return generatedSyntaxTrees;
}

Transduction::SyntaxTree*
Transduction::Replacement::ReplacementExpression::markReplacementPoint(
  Transduction::SymbolTable &symbolTable)
{
  std::cout << "> SETTING REPLACEMENT POINT... ";
  auto replacementPoint = new Transduction::SyntaxTree::ReplacementPoint();

  auto firstTreeFromMainMatch = symbolTable
    .lookup(Nodename::NodenameInfo::MAIN_PLACEHOLDER_NUMBER)
    .second.trees.front();
  firstTreeFromMainMatch->addLeftSibling(replacementPoint);

  std::cout << "DONE\n";
  return replacementPoint;
}

void Transduction::Replacement::ReplacementExpression::injectGeneratedTrees(
  SyntaxTree *replacementPoint, std::vector<SyntaxTree*> &generatedTrees)
{
  if (replacementPoint == nullptr)
  {
    generatedTrees.clear();
    return;
  }

  std::cout << "> INJECTING GENERATED TREES INTO THE REPLACEMENT POINT\n";
  for (auto tree : generatedTrees)
    replacementPoint->addLeftSibling(tree);
  replacementPoint->detachSubtree();
}

void Transduction::Replacement::ReplacementExpression::validate(
  Transduction::Replacement::Contexts::ReplacementValidationContext &context) const
{
  for (auto tree : *treeSequence)
    tree->validate(context);
}
