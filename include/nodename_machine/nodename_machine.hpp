#ifndef NODENAME_MACHINE_HPP
#define NODENAME_MACHINE_HPP

#include <string>
#include <sstream>
#include "nodename_state.hpp"

namespace Nodename {
  class NodenameState;
  class NodenameMachine {
  private:
    bool finished;
    NodenameState* state;
  public:
    NodenameMachine();
    ~NodenameMachine();
    void changeState(NodenameState*);
    void finish();
    void run();
  };
}

#endif
