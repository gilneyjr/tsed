#include "ast-node-data.hpp"

Ast::AstNodeData::AstNodeData(Nodename::NodenameInfo* info)
{
  new (&leaf) AstLeafNodeData{info};
}

Ast::AstNodeData::AstNodeData(
  std::string& operation,
  Nodename::NodenameInfoSet &definitions,
  Nodename::NodenameInfoSet &references
)
{
  new (&internal) AstInternalNodeData{operation, definitions, references};
}

Ast::AstNodeData::~AstNodeData() {}