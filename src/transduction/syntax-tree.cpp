#include "syntax-tree.hpp"
#include <fstream>

Transduction::SyntaxTree::SyntaxTree(
  const std::string tag, SyntaxTree *parent,
  SyntaxTree *firstChild, SyntaxTree *lastChild,
  SyntaxTree *leftSibling, SyntaxTree *rightSibling
) : tag(tag), parent(parent)
  , firstChild(firstChild), lastChild(lastChild)
  , leftSibling(leftSibling), rightSibling(rightSibling)
{
  if (parent == nullptr)
    createEndMarkerAbove(this);

  if (firstChild == nullptr || lastChild == nullptr)
    createEndMarkerBellow(this);
  
  if (leftSibling == nullptr)
    createEndMarkerOnLeftOf(this);

  if (rightSibling == nullptr)
    createEndMarkerOnRightOf(this);
}

Transduction::SyntaxTree::~SyntaxTree()
{
  if (parent != nullptr && parent->_isEndMarker)
  {
    auto endMarkerParent = parent;
    parent->firstChild = nullptr;
    parent->lastChild = nullptr;
    parent = nullptr;
    delete endMarkerParent;
  }

  auto aux = firstChild;
  if (aux != nullptr && aux->leftSibling != nullptr)
    delete aux->leftSibling;

  while (aux != nullptr)
  {
    auto next = aux->rightSibling;
    delete aux;
    aux = next;
  }
}

const std::string& Transduction::SyntaxTree::getTag() const { return tag; }
void Transduction::SyntaxTree::setTag(const std::string &tag) { this->tag = tag; }
Transduction::SyntaxTree* Transduction::SyntaxTree::getParent() const { return parent; }
Transduction::SyntaxTree* Transduction::SyntaxTree::getFirstChild() const { return firstChild; }
Transduction::SyntaxTree* Transduction::SyntaxTree::getLastChild() const { return lastChild; }
Transduction::SyntaxTree* Transduction::SyntaxTree::getLeftSibling() const { return leftSibling; }
Transduction::SyntaxTree* Transduction::SyntaxTree::getRightSibling() const { return rightSibling; }

void Transduction::SyntaxTree::addChild(SyntaxTree *child)
{
  if (child == nullptr)
    return;

  if (child->parent->isEndMarker())
    destroyEndMarker(child->parent);
  child->parent = this;

  if (child->rightSibling == nullptr || !child->rightSibling->isEndMarker())
  {
    child->rightSibling = nullptr;
    createEndMarkerOnRightOf(child);
  }

  if (!lastChild->isEndMarker())
  {
    if (child->leftSibling->isEndMarker())
      destroyEndMarker(child->leftSibling);

    if (lastChild->rightSibling->isEndMarker())
      destroyEndMarker(lastChild->rightSibling);

    child->leftSibling = lastChild;
    lastChild->rightSibling = child;
  }

  lastChild = child;

  if (firstChild->isEndMarker())
  {
    destroyEndMarker(firstChild);
    firstChild = child;
  }
}

void Transduction::SyntaxTree::addLeftSibling(SyntaxTree *newLeftSibling)
{
  if (newLeftSibling == nullptr)
    return;

  newLeftSibling->parent = parent;
  newLeftSibling->leftSibling = leftSibling;

  if (leftSibling != nullptr)
    leftSibling->rightSibling = newLeftSibling;

  newLeftSibling->rightSibling = this;
  leftSibling = newLeftSibling;

  if (parent != nullptr && parent->firstChild == this)
    parent->firstChild = newLeftSibling;
}

void Transduction::SyntaxTree::addRightSibling(SyntaxTree *newRightSibling)
{
  if (newRightSibling == nullptr)
    return;

  newRightSibling->parent = parent;
  newRightSibling->rightSibling = rightSibling;

  if (rightSibling != nullptr)
    rightSibling->leftSibling = newRightSibling;

  newRightSibling->leftSibling = this;
  rightSibling = newRightSibling;

  if (parent != nullptr && parent->lastChild == this)
    parent->lastChild = newRightSibling;
}

bool Transduction::SyntaxTree::isEndMarker()
{
  return _isEndMarker;
}

bool Transduction::SyntaxTree::isInSubtree(SyntaxTree *subtree)
{
  auto node = this;
  if (node->_isEndMarker)
  {
    if (node->parent != nullptr)
      node = node->parent;
    else if (node->leftSibling != nullptr)
      node = node->leftSibling;
    else if (node->rightSibling != nullptr)
      node = node->rightSibling;
  }

  while (node != nullptr)
  {
    if (node == subtree)
      return true;
    node = node->parent;
  }
  return false;
}

Transduction::SyntaxTree* Transduction::SyntaxTree::clone() const
{
  if (_isEndMarker)
    // TODO: should I throw an exception here? "End markers cannot be copied"
    return new EndMarker();

  SyntaxTree* clonedTree = new SyntaxTree(tag);

  SyntaxTree* child = firstChild;
  while (child != nullptr && !child->isEndMarker())
  {
    clonedTree->addChild(child->clone());
    child = child->rightSibling;
  }

  return clonedTree;
}

void Transduction::SyntaxTree::detachSubtree()
{
  // Don't detach end markers because it's necessary to keep them at the extremities of the syntax tree
  if (_isEndMarker)
    return;

  // This node is the root of the syntax tree, so it doesn't need to be detached from it
  if (parent == nullptr || parent->_isEndMarker)
    return;

  // Unique child
  if (parent->firstChild == this && parent->lastChild == this)
  {
    parent->firstChild = parent->lastChild = nullptr;
    if (!parent->_isEndMarker)
      createEndMarkerBellow(parent);
    parent = nullptr;
    createEndMarkerAbove(this);
  }
  // First child
  else if (parent->firstChild == this)
  {
    parent->firstChild = rightSibling;
    parent = nullptr;
    createEndMarkerAbove(this);

    if (rightSibling != nullptr)
    {
      rightSibling->leftSibling = nullptr;
      createEndMarkerOnLeftOf(rightSibling);
      rightSibling = nullptr;
    }
    createEndMarkerOnRightOf(this);
  }
  // Last child
  else if (parent->lastChild == this)
  {
    parent->lastChild = leftSibling;
    parent = nullptr;
    createEndMarkerAbove(this);

    if (leftSibling != nullptr)
    {
      leftSibling->rightSibling = nullptr;
      createEndMarkerOnRightOf(leftSibling);
      leftSibling = nullptr;
    }
    createEndMarkerOnLeftOf(this);
  }
  // Internal child
  else
  {
    parent = nullptr;
    createEndMarkerAbove(this);

    if (leftSibling != nullptr)
      leftSibling->rightSibling = rightSibling;

    if (rightSibling != nullptr)
      rightSibling->leftSibling = leftSibling;

    leftSibling = rightSibling = nullptr;
    createEndMarkerOnLeftOf(this);
    createEndMarkerOnRightOf(this);
  }
}

Transduction::SyntaxTree* Transduction::SyntaxTree::createEndMarkerOnLeftOf(SyntaxTree *tree)
{
  SyntaxTree* result = new EndMarker();
  if (tree == nullptr || tree->leftSibling != nullptr)
    return result;
  result->rightSibling = tree;
  // result->parent = tree->parent; // TODO: Should I keep this code?
  tree->leftSibling = result;
  return result;
}

Transduction::SyntaxTree* Transduction::SyntaxTree::createEndMarkerOnRightOf(SyntaxTree *tree)
{
  SyntaxTree* result = new EndMarker();
  if (tree == nullptr || tree->rightSibling != nullptr)
    return result;
  result->leftSibling = tree;
  // result->parent = tree->parent; // TODO: Should I keep this code?
  tree->rightSibling = result;
  return result;
}

Transduction::SyntaxTree* Transduction::SyntaxTree::createEndMarkerAbove(SyntaxTree *tree)
{
  SyntaxTree* result = new EndMarker();
  if (tree == nullptr || tree->parent != nullptr)
    return result;
  result->firstChild = tree;
  result->lastChild = tree;
  tree->parent = result;
  return result;
}

Transduction::SyntaxTree* Transduction::SyntaxTree::createEndMarkerBellow(SyntaxTree *tree)
{
  SyntaxTree* result = new EndMarker();
  result->_isEndMarker = true;
  if (tree == nullptr)
    return result;
  result->parent = tree;
  tree->firstChild = result;
  tree->lastChild = result;
  return result;
}

void Transduction::SyntaxTree::destroyEndMarker(SyntaxTree *endMarker)
{
  if (!endMarker->_isEndMarker)
    return;

  SyntaxTree *parent = endMarker->getParent();
  SyntaxTree *firstChild = endMarker->getFirstChild();
  SyntaxTree *lastChild = endMarker->getLastChild();
  SyntaxTree *leftSibling = endMarker->getLeftSibling();
  SyntaxTree *rightSibling = endMarker->getRightSibling();

  if (parent != nullptr)
  {
    if (parent->firstChild == endMarker)
      parent->firstChild = nullptr;
    if (parent->lastChild == endMarker)
      parent->lastChild = nullptr;
  }

  if (firstChild != nullptr && firstChild->parent == endMarker)
    firstChild->parent = nullptr;

  if (lastChild != nullptr && lastChild->parent == endMarker)
    lastChild->parent = nullptr;

  if (leftSibling != nullptr && leftSibling->rightSibling == endMarker)
    leftSibling->rightSibling = nullptr;

  if (rightSibling != nullptr && rightSibling->leftSibling == endMarker)
    rightSibling->leftSibling = nullptr;

  endMarker->parent = nullptr;
  endMarker->firstChild = nullptr;
  endMarker->lastChild = nullptr;
  endMarker->leftSibling = nullptr;
  endMarker->rightSibling = nullptr;

  delete endMarker;
}

Transduction::SyntaxTree* Transduction::SyntaxTree::deleteSubtrees(
  std::vector<Transduction::SyntaxTree*> &subtrees)
{
  if (subtrees.empty())
    return new EndMarker();
  
  SyntaxTree* parent = subtrees[0]->parent;
  parent->firstChild = nullptr;
  parent->lastChild = nullptr;

  for (auto *subtree: subtrees)
  {
    subtree->parent = nullptr;
    delete subtree;
  }
  subtrees.clear();

  return createEndMarkerBellow(parent);
}

std::vector<Transduction::SyntaxTree*>
Transduction::SyntaxTree::readFromFile(const std::string& filename)
{
  // <trees>     ::= <tree> <trees_opt>
  // <trees_opt> ::= <trees> | EPS
  // <tree>      ::= "(" WORD <trees> ")" | WORD

  std::ifstream file(filename);

  if (!file.is_open())
  {
    auto msgError = std::string("Error: could not open file: ")
      + filename + ".";
    throw msgError; // TODO: create an exception for this later
  }

  return parseTrees(file);
}

std::string Transduction::SyntaxTree::getNextTokenFromStream(std::istream &in)
{
  char currentChar;
  while (in.get(currentChar) && std::isspace(static_cast<unsigned char>(currentChar)));
  if (in.eof())
    return "";

  if (currentChar == '(' || currentChar == ')')
    return std::string(1, currentChar);

  std::string token(1, currentChar);
  while (in.get(currentChar))
  {
    if (std::isspace(static_cast<unsigned char>(currentChar)) || currentChar == '(' || currentChar == ')')
    {
      in.unget(); 
      break;
    }
    token += currentChar;
  }

  return token;
}

void Transduction::SyntaxTree::putTokenBackToStream(std::string &token, std::istream &in)
{
  for (auto it = token.rbegin(); it != token.rend(); ++it)
    in.putback(*it);
}

std::vector<Transduction::SyntaxTree*> Transduction::SyntaxTree::parseTrees(std::istream &in)
{
  // <trees> ::= <tree> <trees_opt>
  std::vector<SyntaxTree*> trees;

  auto tree = parseTree(in);
  trees.push_back(tree);

  auto trees_opt = parseTreesOpt(in);
  trees.insert(trees.end(), trees_opt.begin(), trees_opt.end());

  return trees;
}

std::vector<Transduction::SyntaxTree*> Transduction::SyntaxTree::parseTreesOpt(std::istream &in)
{
  // <trees_opt> ::= <trees> | EPS
  auto token = getNextTokenFromStream(in);
  putTokenBackToStream(token, in);

  if (in.eof() || token == ")")
    return std::vector<SyntaxTree*>();

  auto trees = parseTrees(in);
  return trees;
}

Transduction::SyntaxTree* Transduction::SyntaxTree::parseTree(std::istream &in)
{
  // <tree> ::= "(" WORD <trees> ")" | WORD
  std::string token = getNextTokenFromStream(in);

  if (token.empty())
    throw std::runtime_error("Error in input tree parsing: unexpected end of file."); // TODO: make an exception for this later

  if (token == ")")
    throw std::runtime_error("Error in input tree parsing: unexpected token \")\"."); // TODO: make an exception for this later

  // "(" WORD <trees> ")"
  if (token == "(")
  {
    std::string word = parseWord(in);
    auto tree = new SyntaxTree(word);

    auto trees = parseTrees(in);
    for (auto *child : trees)
      tree->addChild(child);

    token = getNextTokenFromStream(in);

    if (token.empty())
      throw std::runtime_error("Error in input tree parsing: unexpected end of file."); // TODO: make an exception for this later

    if (token != ")")
      throw std::runtime_error("Error in input tree parsing: unexpected token \"" + token + "\"."); // TODO: make an exception for this later

    return tree;
  }

  // WORD
  return new SyntaxTree(token);
}

std::string Transduction::SyntaxTree::parseWord(std::istream &in)
{
  auto token = getNextTokenFromStream(in);

  if (token.empty())
    throw std::runtime_error("Error in input tree parsing: unexpected end of file."); // TODO: make an exception for this later

  if (token == "(" || token == ")")
    throw std::runtime_error("Error in input tree parsing: unexpected token \"" + token + "\"."); // TODO: make an exception for this later
  
  return token;
}

std::ostream& Transduction::operator<<(std::ostream& os, const SyntaxTree& tree)
{
  if (tree.firstChild == nullptr)
  {
    if (!tree._isEndMarker)
      os << tree.tag;
    return os;
  }
  else if (tree._isEndMarker)
  {
    os << *(tree.firstChild);
    return os;
  }


  if (!tree.firstChild->isEndMarker())
    os << "(";
  os << tree.tag;

  for (auto child = tree.firstChild; child != nullptr; child = child->rightSibling)
  {
    if (!child->_isEndMarker)
      os << " " << *child;
  }

  if (!tree.firstChild->isEndMarker())
    os << ")";

  return os;
}

Transduction::SyntaxTree::EndMarker::EndMarker() : SyntaxTree() 
{
  tag = "#";
  parent = nullptr;
  firstChild = nullptr;
  lastChild = nullptr;
  leftSibling = nullptr;
  rightSibling = nullptr;
  _isEndMarker = true;
}

Transduction::SyntaxTree::ReplacementPoint::ReplacementPoint() : SyntaxTree()
{
  tag = "__ReplacementPoint__";
  parent = nullptr;
  firstChild = nullptr;
  lastChild = nullptr;
  leftSibling = nullptr;
  rightSibling = nullptr;
  _isEndMarker = false;
}
