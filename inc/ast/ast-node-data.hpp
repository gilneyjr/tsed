#ifndef AST_NODE_DATA_HPP
#define AST_NODE_DATA_HPP

#include "ast-internal-node-data.hpp"
#include "ast-leaf-node-data.hpp"
#include "nodename_info.hpp"

namespace Ast
{
  union AstNodeData
  {
    AstLeafNodeData leaf;
    AstInternalNodeData internal;

    AstNodeData(Nodename::NodenameInfo* info);
    AstNodeData(
      std::string& operation,
      Nodename::NodenameInfoSet& definitions,
      Nodename::NodenameInfoSet& references
    );
    ~AstNodeData();
  };
}

#endif