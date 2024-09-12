#ifndef AST_INFO_HPP
#define AST_INFO_HPP

#include <vector>
#include "nodename_result.hpp"

namespace Ast
{
  union AstInfo 
  {
    std::vector<unsigned int> *definedNodenames;
    Nodename::NodenameInfo *nodenameInfo;
  };
}

#endif
