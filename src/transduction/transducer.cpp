#include "transducer.hpp"

#include <map>
#include <regex>
#include <string>
#include <queue>
#include <climits>
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
    std::regex pattern("^" + nodenameInfo->regex + "$");
    std::smatch matches;

    if (std::regex_match(tag, matches, pattern))
    {
      if (nodenameInfo->placeholder != Nodename::Placeholder::NONE)
      {
        Transduction::NodenameMatch match;
        match.left = matches[1];
        match.middle = matches[2];
        match.right = matches[3];
        match.tree = &tree;
        match.placeholder = nodenameInfo->placeholder;
        placeholderMatches[nodenameInfo->placeholderNumber] = match;
      }
      
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
// S < NP & < VP

  if (operation == "&")
  {
    std::map<int, Transduction::NodenameMatch> leftMatches;
    std::map<int, Transduction::NodenameMatch> rightMatches;

    if (!subtreeMatchesSearchExpression(tree, searchExpression->getLeft(), leftMatches))
      return false;

    if (!subtreeMatchesSearchExpression(tree, searchExpression->getRight(), rightMatches))
      return false;
    
    placeholderMatches.insert(leftMatches.begin(), leftMatches.end());
    placeholderMatches.insert(rightMatches.begin(), rightMatches.end());

    return true;
  }

  if (operation == "<")
    return isParentOf(tree, searchExpression->getLeft(), placeholderMatches);

  if (operation == ">")
    return isChildOf(tree, searchExpression->getLeft(), placeholderMatches);

  if (operation == "<,")
    return hasNthChildAs(tree, searchExpression->getLeft(), 1, placeholderMatches);
  
  if (operation == ">,")
    return isNthChildOf(tree, searchExpression->getLeft(), 1, placeholderMatches);

  if (operation == "<-" || operation == "<'")
    return hasNthToLastChildAs(tree, searchExpression->getLeft(), 1, placeholderMatches);
  
  if (operation == ">-" || operation == ">'")
    return isNthToLastChildOf(tree, searchExpression->getLeft(), 1, placeholderMatches);

  std::regex numberedOperationPattern("^([<>]-?)([1-9][0-9]*)$");
  std::smatch matches;
  
  if (std::regex_match(operation, matches, numberedOperationPattern))
  {
    auto op = matches[1].str();
    auto numberStr = matches[2].str();

    unsigned long number = std::stoul(numberStr);
    if (number > UINT_MAX)
      throw "The operator \"" + operation + "\" has a number out of range.";

    if (op == "<")
      return hasNthChildAs(tree, searchExpression->getLeft(), (unsigned int) number, placeholderMatches);

    if (op == ">")
      return isNthChildOf(tree, searchExpression->getLeft(), (unsigned int) number, placeholderMatches);

    if (op == "<-")
      return hasNthToLastChildAs(tree, searchExpression->getLeft(), (unsigned int) number, placeholderMatches);

    if (op == ">-")
      return isNthToLastChildOf(tree, searchExpression->getLeft(), (unsigned int) number, placeholderMatches);
  }

  if (operation == "<:")
    return hasUniqueChildAs(tree, searchExpression->getLeft(), placeholderMatches);

  if (operation == ">:")
    return isUniqueChildOf(tree, searchExpression->getLeft(), placeholderMatches);

  if (operation == "<<")
    return isAncestorOf(tree, searchExpression->getLeft(), placeholderMatches);
  
  if (operation == ">>")
    return isDescendantOf(tree, searchExpression->getLeft(), placeholderMatches);
  
  if (operation == "<<,")
    return hasLeftmostDescendantAs(tree, searchExpression->getLeft(), placeholderMatches);
  
  if (operation == ">>,")
    return isLeftmostDescendantOf(tree, searchExpression->getLeft(), placeholderMatches);

  if (operation == "<<'")
    return hasRightmostDescendantAs(tree, searchExpression->getLeft(), placeholderMatches);
  
  if (operation == ">>'")
    return isRightmostDescendantOf(tree, searchExpression->getLeft(), placeholderMatches);

  if (operation == "<<:")
    return hasUniquePathTo(tree, searchExpression->getLeft(), placeholderMatches);

  if (operation == ">>:")
    return hasUniquePathFrom(tree, searchExpression->getLeft(), placeholderMatches);

  if (operation == "$")
    return isSiblingOf(tree, searchExpression->getLeft(), placeholderMatches);
  
  if (operation == "$..")
    return isLeftSiblingOf(tree, searchExpression->getLeft(), placeholderMatches);

  if (operation == "$,,")
    return isRightSiblingOf(tree, searchExpression->getLeft(), placeholderMatches);

  if (operation == "$.")
    return isImmediatelyLeftSiblingOf(tree, searchExpression->getLeft(), placeholderMatches);

  if (operation == "$,")
    return isImmediatelyRightSiblingOf(tree, searchExpression->getLeft(), placeholderMatches);

  if (operation == "=")
    return isEqualTo(tree, searchExpression->getLeft(), placeholderMatches);

  return false;
}

bool Transduction::Transducer::isParentOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr)
    return false;

  auto child = tree.firstChild;
  while (child != nullptr)
  {
    std::map<int, Transduction::NodenameMatch> matches;
    bool matched = subtreeMatchesSearchExpression(*child, searchExpression, matches);
    if (matched)
    {
      placeholderMatches.insert(matches.begin(), matches.end());
      return true;
    }
    child = child->rightSibling;
  }

  return false;
}

bool Transduction::Transducer::isChildOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr)
    return false;

  std::map<int, Transduction::NodenameMatch> matches;
  bool matched = subtreeMatchesSearchExpression(*(tree.parent), searchExpression, matches);

  if (!matched)
    return false;
  
  placeholderMatches.insert(matches.begin(), matches.end());
  return true;
}

bool Transduction::Transducer::hasNthChildAs(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  unsigned int n,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr || tree.firstChild == nullptr || n == 0)
    return false;

  auto nthChild = tree.firstChild;
  for (auto i = 1u; i < n; i++)
  {
    if (nthChild == nullptr)
      return false;
    nthChild = nthChild->rightSibling;
  }

  std::map<int, Transduction::NodenameMatch> matches;
  bool matched = subtreeMatchesSearchExpression(*nthChild, searchExpression, matches);

  if (!matched)
    return false;
  
  placeholderMatches.insert(matches.begin(), matches.end());
  return true;
}

bool Transduction::Transducer::isNthChildOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  unsigned int n,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr || tree.parent == nullptr || tree.parent->firstChild == nullptr || n == 0)
    return false;

  auto nthChildOfParent = tree.parent->firstChild;
  for (auto i = 1u; i < n; i++)
  {
    if (nthChildOfParent == nullptr)
      return false;
    nthChildOfParent = nthChildOfParent->rightSibling;
  }

  // There is no need to use subtreeMatchesSearchExpression here, because the tree was already matched before
  if (nthChildOfParent != &tree)
    return false;

  // Just try to match the parent
  std::map<int, Transduction::NodenameMatch> matches;
  bool matched = subtreeMatchesSearchExpression(*(tree.parent), searchExpression, matches);

  if (!matched)
    return false;
  
  placeholderMatches.insert(matches.begin(), matches.end());
  return true;
}

bool Transduction::Transducer::hasNthToLastChildAs(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  unsigned int n,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr || tree.lastChild == nullptr || n == 0)
    return false;

  auto nthToLastChild = tree.lastChild;
  for (auto i = n; i > 1u; i--)
  {
    if (nthToLastChild == nullptr)
      return false;
    nthToLastChild = nthToLastChild->leftSibling;
  }

  std::map<int, Transduction::NodenameMatch> matches;
  bool matched = subtreeMatchesSearchExpression(*nthToLastChild, searchExpression, matches);

  if (!matched)
    return false;
  
  placeholderMatches.insert(matches.begin(), matches.end());
  return true;
}

bool Transduction::Transducer::isNthToLastChildOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  unsigned int n,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr || tree.parent == nullptr || tree.parent->lastChild == nullptr || n == 0)
    return false;

  auto nthToLastChildOfParent = tree.parent->lastChild;
  for (auto i = n; i > 1u; i--)
  {
    if (nthToLastChildOfParent == nullptr)
      return false;
    nthToLastChildOfParent = nthToLastChildOfParent->leftSibling;
  }

  // There is no need to use subtreeMatchesSearchExpression here, because the tree was already matched before
  if (nthToLastChildOfParent != &tree)
    return false;

  // Just try to match the parent
  std::map<int, Transduction::NodenameMatch> matches;
  bool matched = subtreeMatchesSearchExpression(*(tree.parent), searchExpression, matches);

  if (!matched)
    return false;
  
  placeholderMatches.insert(matches.begin(), matches.end());
  return true;
}

bool Transduction::Transducer::hasUniqueChildAs(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr || tree.firstChild == nullptr || tree.firstChild != tree.lastChild)
    return false;

  auto& child = *(tree.firstChild);
  std::map<int, Transduction::NodenameMatch> matches;
  bool matched = subtreeMatchesSearchExpression(child, searchExpression, matches);
  if (matched)
  {
    placeholderMatches.insert(matches.begin(), matches.end());
    return true;
  }

  return false;
}

bool Transduction::Transducer::isUniqueChildOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr || tree.parent == nullptr || tree.parent->firstChild == nullptr || tree.parent->firstChild != tree.parent->lastChild)
    return false;

  std::map<int, Transduction::NodenameMatch> matches;
  bool matched = subtreeMatchesSearchExpression(*(tree.parent), searchExpression, matches);

  if (!matched)
    return false;
  
  placeholderMatches.insert(matches.begin(), matches.end());
  return true;
}

bool Transduction::Transducer::isAncestorOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr || tree.firstChild == nullptr)
    return false;

  std::queue<SyntaxTree*> queue;
  for (auto child = tree.firstChild; child != nullptr; child = child->rightSibling)
    queue.push(child);

  while (!queue.empty())
  {
    auto aux = queue.front();
    queue.pop();

    std::map<int, Transduction::NodenameMatch> matches;
    bool matched = subtreeMatchesSearchExpression(*aux, searchExpression, matches);
    if (matched)
    {
      placeholderMatches.insert(matches.begin(), matches.end());
      return true;
    }

    for (auto child = aux->firstChild; child != nullptr; child = child->rightSibling)
      queue.push(child);
  }

  return false;
}

bool Transduction::Transducer::isDescendantOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr || tree.parent == nullptr)
    return false;

  std::queue<SyntaxTree*> queue;

  for (auto ancestor = tree.parent; ancestor != nullptr; ancestor = ancestor->parent)
  {
    std::map<int, Transduction::NodenameMatch> matches;
    bool matched = subtreeMatchesSearchExpression(*ancestor, searchExpression, matches);
    if (matched)
    {
      placeholderMatches.insert(matches.begin(), matches.end());
      return true;
    }
  }

  return false;
}

bool Transduction::Transducer::hasLeftmostDescendantAs(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr || tree.firstChild == nullptr)
    return false;

  auto leftmostDescendant = tree.firstChild;
  while (leftmostDescendant->firstChild != nullptr)
    leftmostDescendant = leftmostDescendant->firstChild;
  
  std::map<int, Transduction::NodenameMatch> matches;
  bool matched = subtreeMatchesSearchExpression(*leftmostDescendant, searchExpression, matches);
  
  if (!matched)
    return false;

  placeholderMatches.insert(matches.begin(), matches.end());
  return true;
}

bool Transduction::Transducer::isLeftmostDescendantOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr || tree.lastChild != nullptr || tree.firstChild != nullptr || tree.parent == nullptr)
    return false;

  for (auto ancestor = tree.parent; ancestor != nullptr; ancestor = ancestor->parent)
  {
    if (ancestor->leftSibling != nullptr) 
      break;

    std::map<int, Transduction::NodenameMatch> matches;
    bool matched = subtreeMatchesSearchExpression(*ancestor, searchExpression, matches);
    
    if (matched)
    {
      placeholderMatches.insert(matches.begin(), matches.end());
      return true;
    }
  }

  return false;
}

bool Transduction::Transducer::hasRightmostDescendantAs(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr || tree.lastChild == nullptr)
    return false;

  auto rightmostDescendant = tree.lastChild;
  while (rightmostDescendant->lastChild != nullptr)
    rightmostDescendant = rightmostDescendant->lastChild;
  
  std::map<int, Transduction::NodenameMatch> matches;
  bool matched = subtreeMatchesSearchExpression(*rightmostDescendant, searchExpression, matches);
  
  if (!matched)
    return false;

  placeholderMatches.insert(matches.begin(), matches.end());
  return true;
}

bool Transduction::Transducer::isRightmostDescendantOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr || tree.lastChild != nullptr || tree.firstChild != nullptr || tree.parent == nullptr)
    return false;

  for (auto ancestor = tree.parent; ancestor != nullptr; ancestor = ancestor->parent)
  {
    if (ancestor->rightSibling != nullptr) 
      break;

    std::map<int, Transduction::NodenameMatch> matches;
    bool matched = subtreeMatchesSearchExpression(*ancestor, searchExpression, matches);
    
    if (matched)
    {
      placeholderMatches.insert(matches.begin(), matches.end());
      return true;
    }
  }

  return false;
}

bool Transduction::Transducer::hasUniquePathTo(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr || tree.firstChild != tree.lastChild || tree.firstChild == nullptr)
    return false;

  auto descendant = tree.firstChild;

  while (descendant != nullptr)
  {
    if (descendant->leftSibling != nullptr || descendant->rightSibling != nullptr)
      return false;
    
    std::map<int, Transduction::NodenameMatch> matches;
    bool matched = subtreeMatchesSearchExpression(*descendant, searchExpression, matches);
    if (matched)
    {
      placeholderMatches.insert(matches.begin(), matches.end());
      return true;
    }

    descendant = descendant->firstChild;
  }

  return false;
}

bool Transduction::Transducer::hasUniquePathFrom(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr || tree.parent == nullptr || tree.leftSibling != nullptr || tree.rightSibling != nullptr)
    return false;

  auto ancestor = tree.parent;

  while (ancestor != nullptr)
  {
    std::map<int, Transduction::NodenameMatch> matches;
    bool matched = subtreeMatchesSearchExpression(*ancestor, searchExpression, matches);
    if (matched)
    {
      placeholderMatches.insert(matches.begin(), matches.end());
      return true;
    }

    if (ancestor->leftSibling != nullptr || ancestor->rightSibling != nullptr)
      return false;

    ancestor = ancestor->parent;
  }

  return false;
}

bool Transduction::Transducer::isSiblingOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  return isLeftSiblingOf(tree, searchExpression, placeholderMatches)
    || isRightSiblingOf(tree, searchExpression, placeholderMatches);
}

bool Transduction::Transducer::isLeftSiblingOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr || tree.leftSibling == nullptr)
    return false;

  auto leftSibling = tree.leftSibling;
  while (leftSibling != nullptr)
  {
    std::map<int, Transduction::NodenameMatch> matches;
    bool matched = subtreeMatchesSearchExpression(*leftSibling, searchExpression, matches);
    if (matched)
    {
      placeholderMatches.insert(matches.begin(), matches.end());
      return true;
    }
    leftSibling = leftSibling->leftSibling;
  }

  return false;
}

bool Transduction::Transducer::isRightSiblingOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr || tree.rightSibling == nullptr)
    return false;

  auto rightSibling = tree.rightSibling;
  while (rightSibling != nullptr)
  {
    std::map<int, Transduction::NodenameMatch> matches;
    bool matched = subtreeMatchesSearchExpression(*rightSibling, searchExpression, matches);
    if (matched)
    {
      placeholderMatches.insert(matches.begin(), matches.end());
      return true;
    }
    rightSibling = rightSibling->rightSibling;
  }

  return false;
}

bool Transduction::Transducer::isImmediatelyLeftSiblingOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr || tree.rightSibling == nullptr)
    return false;

  std::map<int, Transduction::NodenameMatch> matches;
  bool matched = subtreeMatchesSearchExpression(*(tree.rightSibling), searchExpression, matches);

  if (!matched)
    return false;
  
  placeholderMatches.insert(matches.begin(), matches.end());
  return true;
}

bool Transduction::Transducer::isImmediatelyRightSiblingOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr || tree.leftSibling == nullptr)
    return false;

  std::map<int, Transduction::NodenameMatch> matches;
  bool matched = subtreeMatchesSearchExpression(*(tree.leftSibling), searchExpression, matches);

  if (!matched)
    return false;
  
  placeholderMatches.insert(matches.begin(), matches.end());
  return true;
}

bool Transduction::Transducer::isEqualTo(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  std::map<int, Transduction::NodenameMatch> &placeholderMatches)
{
  if (searchExpression == nullptr)
    return false;

  std::map<int, Transduction::NodenameMatch> matches;
  bool matched = subtreeMatchesSearchExpression(tree, searchExpression, matches);

  if (!matched)
    return false;
  
  placeholderMatches.insert(matches.begin(), matches.end());
  return true;
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
      std::cout << *current << std::endl;

      // for (const auto& [key, value] : matches)
      // {
      //   std::cout << (value.placeholder == Nodename::Placeholder::CUT ? "Cut" : "Copy")
      //     << " placeholder " << key << ":" << std::endl;
      //   std::cout << "\tTree tag: " << value.tree->tag << std::endl;
      //   std::cout << "\tLeft: " << value.left << std::endl;
      //   std::cout << "\tMiddle: " << value.middle << std::endl;
      //   std::cout << "\tRight: " << value.right << std::endl;
      // }
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
