#ifndef NODENAME_STATE_HPP
#define NODENAME_STATE_HPP

#include "nodename_machine.hpp"

namespace Nodename
{
  class NodenameState
  {
  protected:
    const NodenameMachine* machine;
  public:
    NodenameState(NodenameMachine*);
    ~NodenameState();
    virtual void run() = 0;
  };
}

#endif 