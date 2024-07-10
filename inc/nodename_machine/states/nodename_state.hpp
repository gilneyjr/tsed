#ifndef NODENAME_STATE_HPP
#define NODENAME_STATE_HPP

#include "nodename_machine.hpp"
#include <iostream>

namespace Nodename
{
  class NodenameMachine;

  class NodenameState
  {
  protected:
    NodenameMachine* machine;
    std::istream& input;
  public:
    NodenameState(NodenameMachine*);
    virtual ~NodenameState();
    virtual NodenameState* run() = 0;
  };
}

#endif
