#ifndef DOUBLE_QUOTED_ESCAPE_NODEBLOCK_STATE_HPP
#define DOUBLE_QUOTED_ESCAPE_NODEBLOCK_STATE_HPP

#include "nodeblock_machine.hpp"
#include "nodeblock_state.hpp"

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