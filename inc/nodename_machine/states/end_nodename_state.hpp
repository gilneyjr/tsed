#ifndef END_NODENAME_STATE_HPP
#define END_NODENAME_STATE_HPP

#include "nodename_state.hpp"

namespace Nodename
{
  class EndNodenameState: public NodenameState
  {
  public:
    EndNodenameState(NodenameMachine*);
    ~EndNodenameState();
    virtual NodenameState* run();
  };
}

#endif
