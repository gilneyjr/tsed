#include "transduction-functions.hpp"

#include <regex>
#include <string>

#include <iostream> // TODO: Remove it later

void Transduction::applyTransductionRule(
  std::list<SyntacticTree*> &trees,
  Ast::AstNode *searchExpression,
  std::vector<Ast::ReplacementNode*> *replacementExpression)
{
  for (SyntacticTree *tree: trees)
    applyTransductionRule(tree, searchExpression, replacementExpression);
}

void Transduction::applyTransductionRule(
  SyntacticTree *tree,
  Ast::AstNode *searchExpression,
  std::vector<Ast::ReplacementNode*> *replacementExpression)
{
  if (tree == nullptr)
    return;

  // std::set<SyntacticTree> modifiedTrees;
  auto it = tree->begin();
  while (it != tree->end())
  {
    // if (modifiedTrees.find(*it) != modifiedTrees.end())
    //   continue;

    if (subtreeMatchesSearchExpression(*it, searchExpression))
    {
      std::cout << "MATCHED: " << it->tag << std::endl;

      // TODO: apply replacement expression here
      // IMPORTANT: The next iterator should be computed before the transduction be performed
      // TODO: insert the cut placeholder nodes into modified trees
      // modifiedTrees.insert(mainPlaceholderNode);
    }

    it++;
  }

  // [NP] ==> PP
  // if (tree == nullptr)
  //   return;

  // // if (searchExpression.data.internal.operation != ":>")
  // //   throw new std::exception("Transductions rules can only be a nodename or restrictions for a nodename"); // TODO: make an exception for this
  
  // // NP >> [0:PP]
  // // NP < [0:PP] // Poderia entrar embaixo do NP, mas não no PP
  // // NP $, [0:PP] // Poderia entrar nos filhos de NP sem problema
  // // NP $. [0:PP] // Não poderia entrar no PP
  // // 3 possíveis comportamentos:
  // // 1. Continua a partir do placeholder como se ele estivesse 
  // //    já sido processado, se ele estiver adiante do tree na preorder.
  // // 2. Armazena em um conjunto as árvores já alteradas e não permite 
  // //    entrar nos filhos delas.
  // // 3. Permitir recursividade
  // if (subtreeMatchesSearchExpression(tree, searchExpression))
  // {
  //   // TODO: apply replacement expression here
  // }
  // else
  // {
  //   for (SyntacticTree *child: tree->children)
  //     applyTransductionRule(child, searchExpression, replacementExpression);
  // }
}

bool Transduction::subtreeMatchesSearchExpression(
  SyntacticTree &tree,
  Ast::AstNode *searchExpression)
{
  if (searchExpression == nullptr)
    return false;

  if (searchExpression->isLeaf())
  {
    // TODO: link Nodename Placeholders to Syntactic Trees here
    Nodename::NodenameInfo *nodenameInfo = searchExpression->data.leaf.nodenameInfo;
    return tagMatchesPattern(tree.tag, nodenameInfo->regex);
  }

  std::string operation = searchExpression->data.internal.operation;

  if (operation == ":>")
  {
    return subtreeMatchesSearchExpression(tree, searchExpression->getLeft())
      && subtreeMatchesSearchExpression(tree, searchExpression->getRight());
  }

  if (operation == "<")
    return isImmediatelyDominatedBy(tree, searchExpression->getLeft());

  return false;
}

bool Transduction::isImmediatelyDominatedBy(SyntacticTree &tree, Ast::AstNode *searchExpression)
{
  if (searchExpression == nullptr)
    return false;

  auto aux = tree.firstChild;
  while (aux != nullptr)
  {
    bool matched = subtreeMatchesSearchExpression(*aux, searchExpression);
    if (matched)
      return true;
    aux = aux->rightSibling;
  }

  return false;
}

bool Transduction::tagMatchesPattern(const std::string &tag, const std::string &pattern)
{
  return std::regex_match(tag, std::regex("^" + pattern + "$"));
}