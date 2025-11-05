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

  if (current->getFirstChild() != nullptr)
    current = current->getFirstChild();
  else if (current->getRightSibling() != nullptr)
    current = current->getRightSibling();
  else
  {
    auto aux = current->getParent();
    while (aux != nullptr)
    {
      if (aux->getRightSibling() != nullptr)
      {
        aux = aux->getRightSibling();
        break;
      }
      aux = aux->getParent();
    }
    current = aux;
  }

  return current;
}
