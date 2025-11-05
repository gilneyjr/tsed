#ifndef END_NODEBLOCK_STATE_HPP
#define END_NODEBLOCK_STATE_HPP

#include "nodeblock-machine.hpp"
#include "nodeblock-state.hpp"

namespace Nodename::Nodeblock
{
  class EndNodeblockState: public NodeblockState
  {
  public:
    EndNodeblockState(NodeblockMachine*);
    ~EndNodeblockState();
    virtual NodeblockState* run();
  };
}

#endif