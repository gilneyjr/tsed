#ifndef DOUBLE_QUOTED_NODEBLOCK_STATE_HPP
#define DOUBLE_QUOTED_NODEBLOCK_STATE_HPP

#include "nodeblock_machine.hpp"
#include "nodeblock_state.hpp"

namespace Nodename::Nodeblock
{
  class DoubleQuotedNodeblockState: public NodeblockState
  {
  public:
    DoubleQuotedNodeblockState(NodeblockMachine*);
    ~DoubleQuotedNodeblockState();
    virtual NodeblockState* run();
  };
}

#endif