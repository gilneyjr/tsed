#ifndef NODENAME_MACHINE_HPP
#define NODENAME_MACHINE_HPP

#include <string>
#include <sstream>

#include "nodename_state.hpp"
#include "nodename_result.hpp"

namespace Nodename {
  class NodenameState;
  class NodenameMachine {
  private:
    bool finished;
    NodenameState* state;
    std::istream& input;
    std::ostream& output;

    Nodename::NodenameResult::NodenameResult* result;
    void resetResult();
  public:
    NodenameMachine(std::istream&, std::ostream&);
    ~NodenameMachine();
    void finish();
    Nodename::NodenameResult::NodenameResult* run();
    std::istream& getInputStream();
    std::ostream& getOutputStream();

    void setResultType(Nodename::NodenameResult::NodenameResultType);
    void setPlaceholder(Nodename::NodenameResult::Placeholder);
    void setPlaceholderNumber(int);
    void appendPlaceholderNumber(int);
    void setUndetermined(bool);
    void setFreeOfContext(bool);
    void setDefOrRef(Nodename::NodenameResult::DefOrRef);
    void setRegex(std::string);
  };
}

#endif
