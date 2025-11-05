#ifndef BEGIN_NODEBLOCK_STATE_HPP
#define BEGIN_NODEBLOCK_STATE_HPP

#include "nodeblock-machine.hpp"
#include "nodeblock-state.hpp"

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