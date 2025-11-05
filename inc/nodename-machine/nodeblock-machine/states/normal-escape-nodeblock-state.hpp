#ifndef NORMAL_ESCAPE_NODEBLOCK_STATE_HPP
#define NORMAL_ESCAPE_NODEBLOCK_STATE_HPP

#include "nodeblock-machine.hpp"
#include "nodeblock-state.hpp"

namespace Nodename::Nodeblock
{
  class NormalEscapeNodeblockState: public NodeblockState
  {
  public:
    NormalEscapeNodeblockState(NodeblockMachine*);
    ~NormalEscapeNodeblockState();
    virtual NodeblockState* run();
  };
}

#endif