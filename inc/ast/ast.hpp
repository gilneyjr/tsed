#ifndef AST_HPP
#define AST_HPP

#include <vector>
#include "ast-info.hpp"

using namespace std;

namespace AST
{
  class AstNode {
  public:
    AstNode* parent;
    AstNode* left;
    AstNode* right;
    AstInfo info;

    AstNode(AstNode* parent, AstNode* left, AstNode* right, AstInfo info);
    ~AstNode();
  };  
}

#endif
