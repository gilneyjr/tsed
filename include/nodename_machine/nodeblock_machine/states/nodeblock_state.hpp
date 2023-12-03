#ifndef NODEBLOCK_STATE_HPP
#define NODEBLOCK_STATE_HPP

#include "nodeblock_machine.hpp"
#include <iostream>

namespace Nodename::Nodeblock
{
  class NodeblockState
  {
  protected:
    NodeblockMachine* machine;
    std::istream& input;
    std::ostream& output;
  public:
    NodeblockState(NodeblockMachine*);
    ~NodeblockState();
    virtual NodeblockState* run() = 0;
  };
}

#endif