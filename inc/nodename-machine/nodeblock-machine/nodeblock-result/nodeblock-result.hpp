#ifndef NODEBLOCK_RESULT_HPP
#define NODEBLOCK_RESULT_HPP

#include <string>

using namespace std;

namespace Nodename::Nodeblock
{
  struct NodeblockResult
  {
    bool undetermined = false;
    std::string regex = "";
  };
}

#endif
