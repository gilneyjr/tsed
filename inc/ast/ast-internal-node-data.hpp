#ifndef AST_INTERNAL_NODE_DATA
#define AST_INTERNAL_NODE_DATA

#include <string>
#include "nodename_info.hpp"

namespace Ast
{
  struct AstInternalNodeData 
  {
    std::string operation;
    Nodename::NodenameInfoSet definitions;
    Nodename::NodenameInfoSet references;

    AstInternalNodeData();

    AstInternalNodeData(
      const std::string &operation,
      const Nodename::NodenameInfoSet& definitions, 
      const Nodename::NodenameInfoSet& references
    );
  };
}

#endif