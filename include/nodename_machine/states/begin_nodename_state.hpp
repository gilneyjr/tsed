#ifndef BEGIN_NODENAME_STATE_HPP
#define BEGIN_NODENAME_STATE_HPP

#include "nodename_machine.hpp"
#include "nodename_state.hpp"

namespace Nodename
{
  class BeginNodenameState: public NodenameState
  {
  public:
    BeginNodenameState(NodenameMachine*);
    ~BeginNodenameState();
    virtual void run();
  };
}

#endif