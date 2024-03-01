#ifndef END_NODEBLOCK_STATE_HPP
#define END_NODEBLOCK_STATE_HPP

#include "nodeblock_machine.hpp"
#include "nodeblock_state.hpp"

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