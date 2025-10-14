#ifndef AST_INFO_HPP
#define AST_INFO_HPP

#include "nodename_info.hpp"

namespace Ast
{
  union AstNodeInfo
  {
    AstLeafNodeInfo leaf;
    AstInternalNodeInfo internal;
  };

  struct AstLeafNodeInfo
  {
    Nodename::NodenameInfo* nodenameInfo;
  };
  
  struct AstInternalNodeInfo 
  {
    std::string operatorLabel; // TODO: think if this is the best way to represent operator information
    Nodename::NodenameInfoSet* definitions;
    Nodename::NodenameInfoSet* references;
  };
}

#endif
