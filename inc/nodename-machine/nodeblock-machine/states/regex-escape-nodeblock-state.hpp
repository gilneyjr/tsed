#ifndef REGEX_ESCAPE_NODEBLOCK_STATE_HPP
#define REGEX_ESCAPE_NODEBLOCK_STATE_HPP

#include "nodeblock-machine.hpp"
#include "nodeblock-state.hpp"

namespace Nodename::Nodeblock
{
  class RegexEscapeNodeblockState: public NodeblockState
  {
  public:
    RegexEscapeNodeblockState(NodeblockMachine*);
    ~RegexEscapeNodeblockState();
    virtual NodeblockState* run();
  };
}

#endif