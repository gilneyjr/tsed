#ifndef NODENAME_MACHINE_HPP
#define NODENAME_MACHINE_HPP

#include <string>
#include <sstream>

#include "nodename_state.hpp"
#include "nodeblock_result.hpp"
#include "nodename_result.hpp"

namespace Nodename {
  class NodenameState;
  class NodenameMachine {
  private:
    bool finished;
    NodenameState* state;
    std::istream& input;
    NodenameResult result;
  public:
    NodenameMachine(std::istream&);
    ~NodenameMachine();
    void finish();
    NodenameResult run();
    std::istream& getInputStream();

    void setResultType(NodenameResultType);
    void setPlaceholder(Placeholder);
    void appendToPlaceholderNumber(int);
    void setFreeOfContext(bool);
    void setDefOrRef(DefOrRef);
    void appendToRegex(std::string);
    void incorporateFrom(Nodeblock::NodeblockResult result);
  };
}

#endif
