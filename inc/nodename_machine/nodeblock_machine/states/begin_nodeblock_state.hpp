#ifndef BEGIN_NODEBLOCK_STATE_HPP
#define BEGIN_NODEBLOCK_STATE_HPP

#include "nodeblock_machine.hpp"
#include "nodeblock_state.hpp"

namespace Nodename::Nodeblock
{
  class BeginNodeblockState: public NodeblockState
  {
  public:
    BeginNodeblockState(NodeblockMachine*);
    ~BeginNodeblockState();
    virtual NodeblockState* run();
  };
}

#endif