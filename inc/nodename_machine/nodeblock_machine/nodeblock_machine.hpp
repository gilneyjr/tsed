#ifndef NODEBLOCK_MACHINE_HPP
#define NODEBLOCK_MACHINE_HPP

#include <iostream>
#include "nodeblock_state.hpp"
#include "nodeblock_result.hpp"

namespace Nodename::Nodeblock
{
  class NodeblockState;
  class NodeblockMachine
  {
  private:
    bool finished;
    NodeblockState* state;
    std::istream& input;
    NodeblockResult result;
  public:
    NodeblockMachine(std::istream&);
    ~NodeblockMachine();
    void finish();
    NodeblockResult run();
    std::istream& getInputStream();
    void setUndetermined(bool);
    void appendToOutput(std::string);
    void appendToOutput(char);
  };
}

#endif