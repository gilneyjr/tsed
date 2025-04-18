#ifndef SYNTAX_TREE_HPP
#define SYNTAX_TREE_HPP

#include <string>

namespace Transduction
{
  class SyntaxTree
  {
  public:
    // TODO: turn some attributes to protected
    std::string tag;
    SyntaxTree* parent;
    SyntaxTree* firstChild;
    SyntaxTree* rightSibling;

    SyntaxTree(const std::string, SyntaxTree* = nullptr);
    ~SyntaxTree();
    void addChild(SyntaxTree*);
  };
}

#endif