#ifndef DOUBLE_QUOTED_ESCAPE_NODEBLOCK_STATE_HPP
#define DOUBLE_QUOTED_ESCAPE_NODEBLOCK_STATE_HPP

#include "nodeblock-machine.hpp"
#include "nodeblock-state.hpp"

namespace Nodename::Nodeblock
{
  class DoubleQuotedEscapeNodeblockState: public NodeblockState
  {
  public:
    DoubleQuotedEscapeNodeblockState(NodeblockMachine*);
    ~DoubleQuotedEscapeNodeblockState();
    virtual NodeblockState* run();
  };
}

#endif