#include "syntax-tree.hpp"

Transduction::SyntaxTree::SyntaxTree(
  const std::string& tag,
  SyntaxTree *parent = nullptr
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

Transduction::SyntaxTree::PreOrderIterator
Transduction::SyntaxTree::begin()
{
  return PreOrderIterator(this);
}

Transduction::SyntaxTree::PreOrderIterator
Transduction::SyntaxTree::end()
{
  return PreOrderIterator(nullptr);
}

Transduction::SyntaxTree::PreOrderIterator::PreOrderIterator(
  Transduction::SyntaxTree::PreOrderIterator::pointer current) : current(current) {}

Transduction::SyntaxTree::PreOrderIterator::reference 
Transduction::SyntaxTree::PreOrderIterator::operator*() const
{
  return *current;
}

Transduction::SyntaxTree::PreOrderIterator::pointer 
Transduction::SyntaxTree::PreOrderIterator::operator->() const
{
  return current;
}

Transduction::SyntaxTree::PreOrderIterator&
Transduction::SyntaxTree::PreOrderIterator::operator++()
{
  if (!current)
    return *this;

  if (current->firstChild != nullptr)
    current = current->firstChild;
  else if (current->rightSibling != nullptr)
    current = current->rightSibling;
  else
  {
    pointer aux = current->parent;
    while (aux != nullptr)
    {
      if (aux->rightSibling != nullptr)
      {
        aux = aux->rightSibling;
        break;
      }
      aux = aux->parent;
    }
    current = aux;
  }
  return *this;
}

Transduction::SyntaxTree::PreOrderIterator
Transduction::SyntaxTree::PreOrderIterator::operator++(int)
{
  PreOrderIterator temp = *this;
  ++(*this);
  return temp;
}

bool Transduction::SyntaxTree::PreOrderIterator::operator==(const PreOrderIterator& other) const
{
  return current == other.current;
}

bool Transduction::SyntaxTree::PreOrderIterator::operator!=(const PreOrderIterator& other) const
{
  return current != other.current;
}