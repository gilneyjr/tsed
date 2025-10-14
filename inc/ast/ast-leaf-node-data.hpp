#ifndef AST_LEAF_NODE_DATA
#define AST_LEAF_NODE_DATA

#include "nodename_info.hpp"

namespace Ast
{
  struct AstLeafNodeData 
  {
    Nodename::NodenameInfo* nodenameInfo;
  };
}

#endif