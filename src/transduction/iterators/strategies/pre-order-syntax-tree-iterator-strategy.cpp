#include "pre-order-syntax-tree-iterator-strategy.hpp"

Transduction::SyntaxTree*
Transduction::PreOrderSyntaxTreeIteratorStrategy::start(SyntaxTree* root)
{
  return root;
}

Transduction::SyntaxTree*
Transduction::PreOrderSyntaxTreeIteratorStrategy::next(SyntaxTree* current)
{
  if (current == nullptr)
    return current;

  if (current->firstChild != nullptr)
    current = current->firstChild;
  else if (current->rightSibling != nullptr)
    current = current->rightSibling;
  else
  {
    auto aux = current->parent;
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

  return current;
}
