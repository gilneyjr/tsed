#ifndef REGEX_NODEBLOCK_STATE_HPP
#define REGEX_NODEBLOCK_STATE_HPP

#include "nodeblock-machine.hpp"
#include "nodeblock-state.hpp"

namespace Nodename::Nodeblock
{
  class RegexNodeblockState: public NodeblockState
  {
  public:
    RegexNodeblockState(NodeblockMachine*);
    ~RegexNodeblockState();
    virtual NodeblockState* run();
  };
}

#endif