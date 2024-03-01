#ifndef SINGLE_QUOTED_NODEBLOCK_STATE_HPP
#define SINGLE_QUOTED_NODEBLOCK_STATE_HPP

#include "nodeblock_machine.hpp"
#include "nodeblock_state.hpp"

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