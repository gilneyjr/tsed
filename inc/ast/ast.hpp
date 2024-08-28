#ifndef AST_HPP
#define AST_HPP

#include <vector>

using namespace std;

namespace AST
{
  class Node {
  public:
    Node* parent;
    Node* left;
    Node* right;
    vector<unsigned int>* defs;

    Node(Node* parent, Node* left, Node* right, vector<unsigned int>* defs);
    ~Node();
  };  
}

AST::Node::Node(Node* parent, Node* left, Node* right, vector<unsigned int>* defs)
{
  this->parent = parent;
  this->left = left;
  this->right = right;
  this-> defs = defs;
}

AST::Node::~Node()
{
  delete left;
  delete right;
  delete defs;
}

#endif
