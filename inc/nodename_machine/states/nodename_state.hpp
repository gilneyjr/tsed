#ifndef NODENAME_STATE_HPP
#define NODENAME_STATE_HPP

#include "nodename_machine.hpp"

namespace Nodename
{
  class NodenameMachine;

  class NodenameState
  {
  protected:
    const NodenameMachine* machine;
  public:
    NodenameState(NodenameMachine*);
    virtual ~NodenameState();
    virtual void run() = 0;
  };
}

#endif 