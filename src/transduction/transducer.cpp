#include "transducer.hpp"

#include <map>
#include <regex>
#include <string>

#include <iostream> // TODO: Remove it later

Transduction::Transducer::Transducer(TransversalStrategy* transversalStrategy)
  : transversalStrategy(transversalStrategy) {}

Transduction::Transducer::~Transducer()
{
  if (this->transversalStrategy)
    delete this->transversalStrategy;
}

bool Transduction::Transducer::subtreeMatchesSearchExpression(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr)
    return false;

  if (searchExpression->isLeaf())
  {
    // TODO: link Nodename Placeholders to Syntax Trees here
    Nodename::NodenameInfo *nodenameInfo = searchExpression->data.leaf.nodenameInfo;

    auto tag = tree.tag;
    std::regex pattern(nodenameInfo->regex);
    std::smatch matches;

    if (std::regex_match(tag, matches, pattern))
    {
      Transduction::NodenameMatch match;
      match.left = matches[1];
      match.middle = matches[2];
      match.right = matches[3];
      match.tree = &tree;
      placeholderMatches[nodenameInfo->placeholderNumber] = match;
      return true;
    }

    return false;
  }

  std::string operation = searchExpression->data.internal.operation;

  // TODO: use factory design pattern here
  if (operation == ":>")
  {
    return subtreeMatchesSearchExpression(tree, searchExpression->getLeft(), placeholderMatches)
      && subtreeMatchesSearchExpression(tree, searchExpression->getRight(), placeholderMatches);
  }

  if (operation == "<")
    return isImmediatelyDominatedBy(tree, searchExpression->getLeft(), placeholderMatches);

  return false;
}

bool Transduction::Transducer::isImmediatelyDominatedBy(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr)
    return false;

  auto aux = tree.firstChild;
  while (aux != nullptr)
  {
    std::map<int, Transduction::NodenameMatch> matches;
    bool matched = subtreeMatchesSearchExpression(*aux, searchExpression, matches);
    if (matched)
    {
      placeholderMatches.insert(matches.begin(), matches.end());
      return true;
    }
    aux = aux->rightSibling;
  }

  return false;
}

bool Transduction::Transducer::tagMatchesPattern(const std::string &tag, const std::string &pattern)
{
  // TODO: procurar algoritmo para determinar estas partes
  // 1 - left
  // - middle
  // - right
  return std::regex_match(tag, std::regex("^" + pattern + "$"));
}

void Transduction::Transducer::applyTransductionRule(
  std::list<SyntaxTree*> &trees,
  Ast::AstNode *searchExpression,
  std::vector<Ast::ReplacementNode*> *replacementExpression)
{
  for (auto *tree: trees)
    applyTransductionRule(tree, searchExpression, replacementExpression);
}

void Transduction::Transducer::applyTransductionRule(
  SyntaxTree *tree,
  Ast::AstNode *searchExpression,
  std::vector<Ast::ReplacementNode*> *replacementExpression)
{
  if (tree == nullptr)
    return;

  // NP < ...

  // std::set<SyntaxTree> modifiedTrees;
  this->transversalStrategy->start(tree); 
  while (this->transversalStrategy->hasNext())
  {
    SyntaxTree* current = this->transversalStrategy->next();
    std::map<int, Transduction::NodenameMatch> matches; 
    if (subtreeMatchesSearchExpression(*current, searchExpression, matches))
    {
      // TODO: remove these cout below
      std::cout << "MATCHED!" << std::endl;
      for (const auto& [key, value] : matches)
      {
        std::cout << "Placeholder " << key << ":" << std::endl;
        std::cout << "\tTree tag: " << value.tree->tag << std::endl;
        std::cout << "\tLeft: " << value.left << std::endl;
        std::cout << "\tMiddle: " << value.middle << std::endl;
        std::cout << "\tRight: " << value.right << std::endl;
      }
      this->transversalStrategy->notifyTransduction();
      // TODO: apply replacement expression here
    }
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
  //   for (SyntaxTree *child: tree->children)
  //     applyTransductionRule(child, searchExpression, replacementExpression);
  // }
}
