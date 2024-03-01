#ifndef NORMAL_NODEBLOCK_STATE_HPP
#define NORMAL_NODEBLOCK_STATE_HPP

#include "nodeblock_machine.hpp"
#include "nodeblock_state.hpp"

namespace Nodename::Nodeblock
{
  class NormalNodeblockState: public NodeblockState
  {
  public:
    NormalNodeblockState(NodeblockMachine*);
    ~NormalNodeblockState();
    virtual NodeblockState* run();
  };
}

#endif