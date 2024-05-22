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
    std::istream& input;
    std::ostream& output;
  public:
    NodenameMachine(std::istream&, std::ostream&);
    ~NodenameMachine();
    void finish();
    void run();
    std::istream& getInputStream();
    std::ostream& getOutputStream();
  };
}

#endif
