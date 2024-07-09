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

    NodeblockResult(bool undetermined, string regex)
    {
      this->undetermined = undetermined;
      this->regex = regex;
    }
  };
}

#endif
