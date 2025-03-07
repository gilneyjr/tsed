#include "syntactic-tree.hpp"

Transduction::SyntacticTree::SyntacticTree(
  const std::string& tag,
  SyntacticTree *parent = nullptr
) : tag(tag), parent(parent) {}

Transduction::SyntacticTree::~SyntacticTree()
{
  auto aux = firstChild;
  while (aux != nullptr)
  {
    delete aux;
    aux = aux->rightSibling;
  }
}

void Transduction::SyntacticTree::addChild(SyntacticTree *child)
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

Transduction::SyntacticTree::PreOrderIterator
Transduction::SyntacticTree::begin()
{
  return PreOrderIterator(this);
}

Transduction::SyntacticTree::PreOrderIterator
Transduction::SyntacticTree::end()
{
  return PreOrderIterator(nullptr);
}

Transduction::SyntacticTree::PreOrderIterator::PreOrderIterator(
  Transduction::SyntacticTree::PreOrderIterator::pointer current) : current(current) {}

Transduction::SyntacticTree::PreOrderIterator::reference 
Transduction::SyntacticTree::PreOrderIterator::operator*() const
{
  return *current;
}

Transduction::SyntacticTree::PreOrderIterator::pointer 
Transduction::SyntacticTree::PreOrderIterator::operator->() const
{
  return current;
}

Transduction::SyntacticTree::PreOrderIterator&
Transduction::SyntacticTree::PreOrderIterator::operator++()
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

Transduction::SyntacticTree::PreOrderIterator
Transduction::SyntacticTree::PreOrderIterator::operator++(int)
{
  PreOrderIterator temp = *this;
  ++(*this);
  return temp;
}

bool Transduction::SyntacticTree::PreOrderIterator::operator==(const PreOrderIterator& other) const
{
  return current == other.current;
}

bool Transduction::SyntacticTree::PreOrderIterator::operator!=(const PreOrderIterator& other) const
{
  return current != other.current;
}