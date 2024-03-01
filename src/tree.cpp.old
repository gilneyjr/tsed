#include "tree.h"
#include <string>
#include <sstream>
#include <vector>

TreeNode::TreeNode( TreeNode* parent, std::string node_name, int born_index )
{
  _data = node_name;
  _parent = parent;
  _children = std::vector<TreeNode*>();
  _born_index = born_index;
}

TreeNode::TreeNode( TreeNode* parent, std::string node_name )
{
  _data = node_name;
  _parent = parent;
  _children = std::vector<TreeNode*>();
  _born_index = 0;
}

TreeNode::~TreeNode()
{
  // write so we avoid memory leaks
  // special attention to the rule of three
}

std::string& TreeNode::data()
{
  return _data;
}

void TreeNode::add_child( TreeNode* tree_node )
{
  tree_node->_born_index = children_amount();
  _children.push_back(tree_node);
}

int TreeNode::children_amount()
{
  return _children.size();
}

bool TreeNode::is_root()
{
  return _parent == NULL;
}

bool TreeNode::is_leaf()
{
  return _children.size() == 0;
}

bool TreeNode::is_rightmost_sibling()
{
  if(is_root()) return true;

  return _born_index + 1 == _parent->children_amount();
}

bool TreeNode::is_leftmost_sibling()
{
  if(is_root()) return true;

  return _born_index == 0;
}

std::string TreeNode::build_tree()
{
  // MUST be optimized

  std::stringstream output;

  if(is_leaf())
  {
    output << " ";
    output << _data;
    return output.str();
  }

  output << "(" << _data;

  for( int i = 0; i < children_amount(); i++ )
  {
    output << " " << _children[i]->build_tree();
  }

  output << ")";

  return output.str();
}

std::string TreeNode::build_pretty_tree(int level)
{
  // MUST be optimized

  std::stringstream output;

  if(is_leaf())
  {
    output << " ";
    output << _data;
    return output.str();
  }

  if(level) output << "\n";

  for( int l = 0; l < level; l++ ) output << "  ";
  output << "(" << _data;

  for( int i = 0; i < children_amount(); i++ )
  {
    output << " " << _children[i]->build_pretty_tree(level + 1);
  }

  output << ")";

  return output.str();
}

TreeNode* TreeNode::parent()
{
  return _parent;
}

std::vector< TreeNode* > TreeNode::children()
{
  return _children;
}
