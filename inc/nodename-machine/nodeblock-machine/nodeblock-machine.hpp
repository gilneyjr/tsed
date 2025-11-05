#ifndef NODEBLOCK_MACHINE_HPP
#define NODEBLOCK_MACHINE_HPP

#include <iostream>
#include "nodeblock-state.hpp"
#include "nodeblock-result.hpp"

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
    void appendToOutput(char);
  };
}

#endif