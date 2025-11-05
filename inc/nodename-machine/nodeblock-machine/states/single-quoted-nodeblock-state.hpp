#ifndef SINGLE_QUOTED_NODEBLOCK_STATE_HPP
#define SINGLE_QUOTED_NODEBLOCK_STATE_HPP

#include "nodeblock-machine.hpp"
#include "nodeblock-state.hpp"

namespace Nodename::Nodeblock
{
  class SingleQuotedNodeblockState: public NodeblockState
  {
  public:
    SingleQuotedNodeblockState(NodeblockMachine*);
    ~SingleQuotedNodeblockState();
    virtual NodeblockState* run();
  };
}

#endif