#ifndef NODENAME_MATCH_HPP
#define NODENAME_MATCH_HPP

#include <string>
#include <vector>
#include "placeholder.hpp"
#include "syntax-tree.hpp"

namespace Transduction
{
  struct NodenameMatch
  {
    bool isRange;
    std::string left;
    std::string middle;
    std::string right;
    Nodename::Placeholder placeholder;
    std::vector<SyntaxTree*> trees;

    NodenameMatch clone() const;
    bool matchedIsRoot();
  };
}

#endif
