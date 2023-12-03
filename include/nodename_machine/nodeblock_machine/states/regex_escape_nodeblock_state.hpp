#ifndef REGEX_ESCAPE_NODEBLOCK_STATE_HPP
#define REGEX_ESCAPE_NODEBLOCK_STATE_HPP

#include "nodeblock_machine.hpp"
#include "nodeblock_state.hpp"

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