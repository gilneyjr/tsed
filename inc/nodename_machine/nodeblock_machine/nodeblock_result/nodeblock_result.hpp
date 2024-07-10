#ifndef NODEBLOCK_RESULT_HPP
#define NODEBLOCK_RESULT_HPP

#include <string>

using namespace std;

namespace Nodename::Nodeblock
{
  struct NodeblockResult
  {
    bool undetermined;
    std::string regex;

    NodeblockResult() // TODO: mover construtor para arquivo .cpp
    {
      this->undetermined = false;
      this->regex = "";
    }
  };
}

#endif
