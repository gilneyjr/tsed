#ifndef NORMAL_ESCAPE_NODEBLOCK_STATE_HPP
#define NORMAL_ESCAPE_NODEBLOCK_STATE_HPP

#include "nodeblock_machine.hpp"
#include "nodeblock_state.hpp"

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