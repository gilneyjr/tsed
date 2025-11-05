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
  SymbolTable &symbolTable)
{
  if (searchExpression == nullptr)
    return false;

  if (searchExpression->isLeaf())
  {
    Nodename::NodenameInfo *nodenameInfo = searchExpression->data.leaf.nodenameInfo;
    if (nodenameInfo->defOrRef == Nodename::DefOrRef::REFERENCE)
    {
      auto result = symbolTable.lookup(nodenameInfo->placeholderNumber);
      if (!result.first)
        return false;
      return &tree == result.second.tree;
    }

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
        symbolTable.insert(nodenameInfo->placeholderNumber, match);
      }
      
      return true;
    }

    return false;
  }

  std::string operation = searchExpression->data.internal.operation;

  // TODO: use factory design pattern here
  if (operation == ":>" || operation == "&")
  {
    symbolTable.enterScope();

    bool matched = subtreeMatchesSearchExpression(tree, searchExpression->getLeft(), symbolTable)
      && subtreeMatchesSearchExpression(tree, searchExpression->getRight(), symbolTable);

    if (!matched)
    {
      symbolTable.exitScope();
      return false;
    }

    return true;
  }

  if (operation == "|")
  {
    symbolTable.enterScope();
    bool matched = subtreeMatchesSearchExpression(tree, searchExpression->getLeft(), symbolTable)
      || subtreeMatchesSearchExpression(tree, searchExpression->getRight(), symbolTable);

    if (!matched)
    {
      symbolTable.exitScope();
      return false;
    }

    return true;
  }

  if (operation == "!")
  {
    symbolTable.enterScope();
    bool matched = !subtreeMatchesSearchExpression(tree, searchExpression->getLeft(), symbolTable);
    symbolTable.exitScope(); // all matches found in negation are discarded
    return matched;
  }

  if (operation == "<")
    return isParentOf(tree, searchExpression->getLeft(), symbolTable);

  if (operation == ">")
    return isChildOf(tree, searchExpression->getLeft(), symbolTable);

  if (operation == "<,")
    return hasNthChildAs(tree, searchExpression->getLeft(), 1, symbolTable);
  
  if (operation == ">,")
    return isNthChildOf(tree, searchExpression->getLeft(), 1, symbolTable);

  if (operation == "<-" || operation == "<'")
    return hasNthToLastChildAs(tree, searchExpression->getLeft(), 1, symbolTable);
  
  if (operation == ">-" || operation == ">'")
    return isNthToLastChildOf(tree, searchExpression->getLeft(), 1, symbolTable);

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
      return hasNthChildAs(tree, searchExpression->getLeft(), (unsigned int) number, symbolTable);

    if (op == ">")
      return isNthChildOf(tree, searchExpression->getLeft(), (unsigned int) number, symbolTable);

    if (op == "<-")
      return hasNthToLastChildAs(tree, searchExpression->getLeft(), (unsigned int) number, symbolTable);

    if (op == ">-")
      return isNthToLastChildOf(tree, searchExpression->getLeft(), (unsigned int) number, symbolTable);
  }

  if (operation == "<:")
    return hasUniqueChildAs(tree, searchExpression->getLeft(), symbolTable);

  if (operation == ">:")
    return isUniqueChildOf(tree, searchExpression->getLeft(), symbolTable);

  if (operation == "<<")
    return isAncestorOf(tree, searchExpression->getLeft(), symbolTable);
  
  if (operation == ">>")
    return isDescendantOf(tree, searchExpression->getLeft(), symbolTable);
  
  if (operation == "<<,")
    return hasLeftmostDescendantAs(tree, searchExpression->getLeft(), symbolTable);
  
  if (operation == ">>,")
    return isLeftmostDescendantOf(tree, searchExpression->getLeft(), symbolTable);

  if (operation == "<<'")
    return hasRightmostDescendantAs(tree, searchExpression->getLeft(), symbolTable);
  
  if (operation == ">>'")
    return isRightmostDescendantOf(tree, searchExpression->getLeft(), symbolTable);

  if (operation == "<<:")
    return hasUniquePathTo(tree, searchExpression->getLeft(), symbolTable);

  if (operation == ">>:")
    return hasUniquePathFrom(tree, searchExpression->getLeft(), symbolTable);

  if (operation == "$")
    return isSiblingOf(tree, searchExpression->getLeft(), symbolTable);
  
  if (operation == "$..")
    return isLeftSiblingOf(tree, searchExpression->getLeft(), symbolTable);

  if (operation == "$,,")
    return isRightSiblingOf(tree, searchExpression->getLeft(), symbolTable);

  if (operation == "$.")
    return isImmediatelyLeftSiblingOf(tree, searchExpression->getLeft(), symbolTable);

  if (operation == "$,")
    return isImmediatelyRightSiblingOf(tree, searchExpression->getLeft(), symbolTable);

  if (operation == "=")
    return isEqualTo(tree, searchExpression->getLeft(), symbolTable);

  return false;
}

bool Transduction::Transducer::isParentOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  SymbolTable& symbolTable)
{
  if (searchExpression == nullptr)
    return false;

  for (auto child = tree.firstChild; child != nullptr; child = child->rightSibling)
    if (subtreeMatchesSearchExpression(*child, searchExpression, symbolTable))
      return true;
  return false;
}

bool Transduction::Transducer::isChildOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  SymbolTable& symbolTable)
{
  if (searchExpression == nullptr || tree.parent == nullptr)
    return false;
  return subtreeMatchesSearchExpression(*(tree.parent), searchExpression, symbolTable);
}

bool Transduction::Transducer::hasNthChildAs(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  unsigned int n,
  SymbolTable& symbolTable)
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

  return subtreeMatchesSearchExpression(*nthChild, searchExpression, symbolTable);
}

bool Transduction::Transducer::isNthChildOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  unsigned int n,
  SymbolTable& symbolTable)
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

  return nthChildOfParent == &tree && subtreeMatchesSearchExpression(*(tree.parent), searchExpression, symbolTable);
}

bool Transduction::Transducer::hasNthToLastChildAs(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  unsigned int n,
  SymbolTable& symbolTable)
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

  return subtreeMatchesSearchExpression(*nthToLastChild, searchExpression, symbolTable);
}

bool Transduction::Transducer::isNthToLastChildOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  unsigned int n,
  SymbolTable& symbolTable)
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

  return nthToLastChildOfParent == &tree && subtreeMatchesSearchExpression(*(tree.parent), searchExpression, symbolTable);
}

bool Transduction::Transducer::hasUniqueChildAs(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  SymbolTable& symbolTable)
{
  if (searchExpression == nullptr || tree.firstChild == nullptr || tree.firstChild != tree.lastChild)
    return false;
  return subtreeMatchesSearchExpression(*(tree.firstChild), searchExpression, symbolTable);
}

bool Transduction::Transducer::isUniqueChildOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  SymbolTable& symbolTable)
{
  if (searchExpression == nullptr || tree.parent == nullptr || tree.parent->firstChild == nullptr || tree.parent->firstChild != tree.parent->lastChild)
    return false;
  return subtreeMatchesSearchExpression(*(tree.parent), searchExpression, symbolTable);
}

bool Transduction::Transducer::isAncestorOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  SymbolTable& symbolTable)
{
  if (searchExpression == nullptr || tree.firstChild == nullptr)
    return false;

  // TODO: should I use tree tranversal strategies here?
  std::queue<SyntaxTree*> queue;
  for (auto child = tree.firstChild; child != nullptr; child = child->rightSibling)
    queue.push(child);

  while (!queue.empty())
  {
    auto descendant = queue.front();
    queue.pop();

    if (subtreeMatchesSearchExpression(*descendant, searchExpression, symbolTable))
      return true;

    for (auto child = descendant->firstChild; child != nullptr; child = child->rightSibling)
      queue.push(child);
  }

  return false;
}

bool Transduction::Transducer::isDescendantOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  SymbolTable& symbolTable)
{
  if (searchExpression == nullptr || tree.parent == nullptr)
    return false;

  for (auto ancestor = tree.parent; ancestor != nullptr; ancestor = ancestor->parent)
    if (subtreeMatchesSearchExpression(*ancestor, searchExpression, symbolTable))
      return true;
  return false;
}

bool Transduction::Transducer::hasLeftmostDescendantAs(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  SymbolTable& symbolTable)
{
  if (searchExpression == nullptr || tree.firstChild == nullptr)
    return false;

  auto leftmostDescendant = tree.firstChild;
  while (leftmostDescendant->firstChild != nullptr)
    leftmostDescendant = leftmostDescendant->firstChild;

  return subtreeMatchesSearchExpression(*leftmostDescendant, searchExpression, symbolTable);
}

bool Transduction::Transducer::isLeftmostDescendantOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  SymbolTable& symbolTable)
{
  if (searchExpression == nullptr || tree.lastChild != nullptr || tree.firstChild != nullptr || tree.parent == nullptr)
    return false;

  for (auto ancestor = tree.parent; ancestor != nullptr; ancestor = ancestor->parent)
  {
    if (ancestor->leftSibling != nullptr) 
      break;

    if (subtreeMatchesSearchExpression(*ancestor, searchExpression, symbolTable))
      return true;
  }

  return false;
}

bool Transduction::Transducer::hasRightmostDescendantAs(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  SymbolTable& symbolTable)
{
  if (searchExpression == nullptr || tree.lastChild == nullptr)
    return false;

  auto rightmostDescendant = tree.lastChild;
  while (rightmostDescendant->lastChild != nullptr)
    rightmostDescendant = rightmostDescendant->lastChild;

  return subtreeMatchesSearchExpression(*rightmostDescendant, searchExpression, symbolTable);
}

bool Transduction::Transducer::isRightmostDescendantOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  SymbolTable& symbolTable)
{
  if (searchExpression == nullptr || tree.lastChild != nullptr || tree.firstChild != nullptr || tree.parent == nullptr)
    return false;

  for (auto ancestor = tree.parent; ancestor != nullptr; ancestor = ancestor->parent)
  {
    if (ancestor->rightSibling != nullptr) 
      break;

    if (subtreeMatchesSearchExpression(*ancestor, searchExpression, symbolTable))
      return true;
  }

  return false;
}

bool Transduction::Transducer::hasUniquePathTo(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  SymbolTable& symbolTable)
{
  if (searchExpression == nullptr || tree.firstChild != tree.lastChild || tree.firstChild == nullptr)
    return false;

  for (auto descendant = tree.firstChild; descendant != nullptr; descendant = descendant->firstChild)
  {
    if (descendant->leftSibling != nullptr || descendant->rightSibling != nullptr)
      return false;

    if (subtreeMatchesSearchExpression(*descendant, searchExpression, symbolTable))
      return true;
  }

  return false;
}

bool Transduction::Transducer::hasUniquePathFrom(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  SymbolTable& symbolTable)
{
  if (searchExpression == nullptr || tree.parent == nullptr || tree.leftSibling != nullptr || tree.rightSibling != nullptr)
    return false;

  for (auto ancestor = tree.parent; ancestor != nullptr; ancestor = ancestor->parent)
  {
    if (subtreeMatchesSearchExpression(*ancestor, searchExpression, symbolTable))
      return true;

    if (ancestor->leftSibling != nullptr || ancestor->rightSibling != nullptr)
      break;
  }

  return false;
}

bool Transduction::Transducer::isSiblingOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  SymbolTable& symbolTable)
{
  // TODO: verify what matches precedence should be used here
  return isLeftSiblingOf(tree, searchExpression, symbolTable)
    || isRightSiblingOf(tree, searchExpression, symbolTable);
}

bool Transduction::Transducer::isLeftSiblingOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  SymbolTable& symbolTable)
{
  if (searchExpression == nullptr || tree.leftSibling == nullptr)
    return false;

  // TODO: verify what matches precedence should be used here
  for (auto leftSibling = tree.leftSibling; leftSibling != nullptr; leftSibling = leftSibling->leftSibling)
    if (subtreeMatchesSearchExpression(*leftSibling, searchExpression, symbolTable))
      return true;

  return false;
}

bool Transduction::Transducer::isRightSiblingOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  SymbolTable& symbolTable)
{
  if (searchExpression == nullptr || tree.rightSibling == nullptr)
    return false;

  // TODO: verify what matches precedence should be used here
  for (auto rightSibling = tree.rightSibling; rightSibling != nullptr; rightSibling = rightSibling->rightSibling)
    if (subtreeMatchesSearchExpression(*rightSibling, searchExpression, symbolTable))
      return true;

  return false;
}

bool Transduction::Transducer::isImmediatelyLeftSiblingOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  SymbolTable& symbolTable)
{
  if (searchExpression == nullptr || tree.rightSibling == nullptr)
    return false;
  return subtreeMatchesSearchExpression(*(tree.rightSibling), searchExpression, symbolTable);
}

bool Transduction::Transducer::isImmediatelyRightSiblingOf(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  SymbolTable& symbolTable)
{
  if (searchExpression == nullptr || tree.leftSibling == nullptr)
    return false;
  return subtreeMatchesSearchExpression(*(tree.leftSibling), searchExpression, symbolTable);
}

bool Transduction::Transducer::isEqualTo(
  SyntaxTree &tree,
  Ast::AstNode *searchExpression,
  SymbolTable& symbolTable)
{
  if (searchExpression == nullptr)
    return false;
  return subtreeMatchesSearchExpression(tree, searchExpression, symbolTable);
}

void Transduction::Transducer::apply(TransductionRule *rule, SyntaxTree* tree)
{
  if (rule == nullptr || tree == nullptr)
    return;

  transversalStrategy->start(tree);
  while (transversalStrategy->hasNext())
  {
    SyntaxTree* current = transversalStrategy->next();
    SymbolTable symbolTable;
    if (rule->search->match(current, symbolTable))
    {
      std::cout << *current << std::endl;
      this->transversalStrategy->notifyTransduction();
      // TODO: apply replacement expression here
    }
  }
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

  // std::set<SyntaxTree> modifiedTrees;
  this->transversalStrategy->start(tree);

  while (this->transversalStrategy->hasNext())
  {
    SyntaxTree* current = this->transversalStrategy->next();
    SymbolTable symbolTable;
    if (subtreeMatchesSearchExpression(*current, searchExpression, symbolTable))
    {
      std::cout << *current << std::endl;
      this->transversalStrategy->notifyTransduction();
      // TODO: apply replacement expression here
    }
  }

  // TODO: remove these comments later
  // NP >> [0:PP]
  // NP < [0:PP] // Poderia entrar embaixo do NP, mas não no PP
  // NP $, [0:PP] // Poderia entrar nos filhos de NP sem problema
  // NP $. [0:PP] // Não poderia entrar no PP
  // 3 possíveis comportamentos:
  // 1. Continua a partir do placeholder como se ele estivesse 
  //    já sido processado, se ele estiver adiante do tree na preorder.
  // 2. Armazena em um conjunto as árvores já alteradas e não permite 
  //    entrar nos filhos delas.
  // 3. Permitir recursividade
}
