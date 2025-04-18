#include "syntax-tree.hpp"

Transduction::SyntaxTree::SyntaxTree(
  const std::string tag,
  SyntaxTree *parent
) : tag(tag), parent(parent) {}

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
