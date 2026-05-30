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
  {
    if (current->getFirstChild()->getLeftSibling() != nullptr
      && current->getFirstChild()->getLeftSibling()->isEndMarker())
    {
      current = current->getFirstChild()->getLeftSibling();
    }
    else
      current = current->getFirstChild();
  }
  else if (current->getRightSibling() != nullptr)
    current = current->getRightSibling();
  else
  {
    if (current->isEndMarker() && current->getLeftSibling() != nullptr)
      current = current->getLeftSibling();

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

Transduction::IteratorDirection Transduction::PreOrderSyntaxTreeIteratorStrategy::direction()
{
  return IteratorDirection::FORWARD;
}
