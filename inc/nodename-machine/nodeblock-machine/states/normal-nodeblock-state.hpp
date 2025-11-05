#ifndef NORMAL_NODEBLOCK_STATE_HPP
#define NORMAL_NODEBLOCK_STATE_HPP

#include "nodeblock-machine.hpp"
#include "nodeblock-state.hpp"

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