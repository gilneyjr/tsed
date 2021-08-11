#include "ptb_interpreter.h"

#include <vector>
#include <string>

#include <ctype.h>

#include <iostream>

#define TRAVERSE_STATE 0
#define NAMING_STATE 1

PTBInterpreter::PTBInterpreter( std::string input )
{
  input.push_back(' ');
  _input = input;

  position = 0;
  state = TRAVERSE_STATE;

  head = 1;
  root = new TreeNode(NULL, std::string("ROOT"));
  tree_node = NULL;
  name_consumed = 0;
}

TreeNode* PTBInterpreter::parse()
{
  input_size = _input.length();

  /* debug
  std::cout << _input << std::endl;
  std::cout << "recebi um input de tamanho: " << input_size << std::endl;
  */

  while(position < input_size)
  {
    /* debug
    std::cout << "---------------------------------" << std::endl;
    std::cout << _input << std::endl;
    for(int i=0; i < position; i++) std::cout<<" ";
    std::cout<<"^"<<std::endl;

    if(state==0)
      std::cout << " position: " << position << "   state: TRAVERSE " << std::endl;
    else
      std::cout << " position: " << position << "   state: NAMING " << std::endl;

    std::cout<<" root: "<<std::endl;
    std::cout<<root->build_pretty_tree(0)<<std::endl;
    if(tree_node)
    {
      std::cout<<" tree-node: "<<std::endl;
      std::cout<<tree_node->build_pretty_tree(0)<<std::endl;
    }
    else
    {
      std::cout<<" tree-node: "<<std::endl;
      std::cout<<"   nil"<<std::endl;
    }

    std::cout<<" buffer: "<<buffer<<std::endl;

    std::cout<<" named_level: "<<std::endl<<"  ";
    for(int i=0;i<named_level.size();i++)
      if(named_level[i]) std::cout<<"T";
      else std::cout<<"F";

    std::cout<<std::endl;

    std::cout<<" head: "<<(int) head<<std::endl;
    */

    switch(state)
    {
      case TRAVERSE_STATE: traverse_flow();
      break;
      case NAMING_STATE: naming_flow();
      break;
    }

    if(!errors.empty())
    {
      break;
    }
  }

  return root->children()[0];
}

void PTBInterpreter::traverse_flow()
{
  char current = _input[position];

  if( current == ' ' || current == '\n' )
  {
    if(!buffer.empty())
    {
      if(head)
      {
        root->add_child(tree_node);
        root = tree_node;
        buffer = std::string();
      }
      else
      {
        root->add_child(tree_node);
        buffer = std::string();
      }

      head = false;
    }
  }
  else if( current == '(' )
  {
    head = true;
    named_level.push_back(false);
  }
  else if( current == ')' )
  {
    if(named_level.back())
    {
      // represents a node

      if(!buffer.empty())
      {
        root->add_child(tree_node);
        buffer = std::string();
      }

      root = root->parent();
    }
    else
    {
      // just an extraneous pair of ()
    }

    named_level.pop_back();
  }
  else
  {
    buffer = std::string();
    buffer.push_back(current);
    state = NAMING_STATE;
  }

  if( errors.empty() ) position++;
}

void PTBInterpreter::naming_flow()
{
  char current = _input[position];

  if( current == ' ' || current == '\n' || current == '(' || current == ')' )
  {
    state = TRAVERSE_STATE;
    name_consumed = 0;

    if(named_level.empty())
    {
        tree_node = new TreeNode(root, buffer);
    }
    else if(true)
    {
        tree_node = new TreeNode(root, buffer);
        named_level.back() = true;
    }
    else
    {
        named_level.back() = true;
    }

  }
  else
  {
    buffer.push_back(current);
    position++;
  }
}
