#ifndef DOUBLE_QUOTED_NODEBLOCK_STATE_HPP
#define DOUBLE_QUOTED_NODEBLOCK_STATE_HPP

#include "nodeblock-machine.hpp"
#include "nodeblock-state.hpp"

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