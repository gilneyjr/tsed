#include "traversal-behavior-test-utils.hpp"

Transduction::SyntaxTree* createNullTree()
{
  return nullptr;
}

Transduction::SyntaxTree* createEmptyTree()
{
  return new Transduction::SyntaxTree::EndMarker();
}

Transduction::SyntaxTree* createSingleNodeTree()
{
  return new Transduction::SyntaxTree("S");
}

Transduction::SyntaxTree* createRepresentativeTree()
{
  auto S = new Transduction::SyntaxTree("S");

  auto A1 = new Transduction::SyntaxTree("A1");
  auto A2 = new Transduction::SyntaxTree("A2");
  auto A3 = new Transduction::SyntaxTree("A3");

  auto B1 = new Transduction::SyntaxTree("B1");
  auto B2 = new Transduction::SyntaxTree("B2");
  auto B3 = new Transduction::SyntaxTree("B3");
  auto B4 = new Transduction::SyntaxTree("B4");
  auto B5 = new Transduction::SyntaxTree("B5");
  auto B6 = new Transduction::SyntaxTree("B6");
  auto B7 = new Transduction::SyntaxTree("B7");
  auto B8 = new Transduction::SyntaxTree("B8");
  auto B9 = new Transduction::SyntaxTree("B9");

  S->addChild(A1);
  S->addChild(A2);
  S->addChild(A3);

  A1->addChild(B1);
  A1->addChild(B2);
  A1->addChild(B3);

  A2->addChild(B4);
  A2->addChild(B5);
  A2->addChild(B6);

  A3->addChild(B7);
  A3->addChild(B8);
  A3->addChild(B9);

  return S;
}