#ifndef NODENAME_MATCH_HPP
#define NODENAME_MATCH_HPP

#include <string>
#include "placeholder.hpp"
#include "syntax-tree.hpp"

namespace Transduction
{
  struct NodenameMatch
  {
    std::string left;
    std::string middle;
    std::string right;
    Nodename::Placeholder placeholder;
    SyntaxTree* tree;
  };
}

#endif
