#ifndef SINGLE_QUOTED_ESCAPE_NODEBLOCK_STATE_HPP
#define SINGLE_QUOTED_ESCAPE_NODEBLOCK_STATE_HPP

#include "nodeblock-machine.hpp"
#include "nodeblock-state.hpp"

namespace Nodename::Nodeblock
{
  class SingleQuotedEscapeNodeblockState: public NodeblockState
  {
  public:
    SingleQuotedEscapeNodeblockState(NodeblockMachine*);
    ~SingleQuotedEscapeNodeblockState();
    virtual NodeblockState* run();
  };
}

#endif