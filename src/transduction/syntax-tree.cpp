#include "syntax-tree.hpp"
#include <fstream>
#include <iostream> // TODO: remove it later

Transduction::SyntaxTree::SyntaxTree(
  const std::string tag,
  SyntaxTree *parent
) : tag(tag), parent(parent), firstChild(nullptr), rightSibling(nullptr) {}

Transduction::SyntaxTree::~SyntaxTree()
{
  auto aux = firstChild;
  while (aux != nullptr)
  {
    delete aux;
    aux = aux->rightSibling;
  }
}

void Transduction::SyntaxTree::addChild(SyntaxTree *child)
{
  if (child == nullptr)
    return;

  child->parent = this;
  child->rightSibling = nullptr;

  if (firstChild == nullptr)
  {
    firstChild = child;
    return;
  }

  auto aux = firstChild;
  while (aux != nullptr && aux->rightSibling != nullptr)
    aux = aux->rightSibling;
  aux->rightSibling = child;
}

std::vector<Transduction::SyntaxTree*>
Transduction::SyntaxTree::readFromFile(std::string& filename)
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
  for (auto it = token.rbegin(); it != token.rend(); it++)
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

// TODO: remove this method later
void Transduction::SyntaxTree::printTree(SyntaxTree* tree, int pad)
{
  if (tree == nullptr)
    return;
  
  for (int i = 0; i < pad; i++)
    std::cout << " ";
  std::cout << tree->tag << std::endl;
  
  auto work = tree->firstChild;
  while (work != nullptr)
  {
    printTree(work, pad+1);
    work = work->rightSibling;
  }
}