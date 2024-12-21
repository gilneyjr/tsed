#include "ast-internal-node-data.hpp"

Ast::AstInternalNodeData::AstInternalNodeData() {}

Ast::AstInternalNodeData::AstInternalNodeData(
  const std::string &operation,
  const Nodename::NodenameInfoSet& definitions,
  const Nodename::NodenameInfoSet& references
) : operation(operation), definitions(definitions), references(references) {}