#ifndef NODEBLOCK_STATE_HPP
#define NODEBLOCK_STATE_HPP

#include "nodeblock_machine.hpp"
#include <iostream>

namespace Nodename::Nodeblock
{
  class NodeblockMachine;
  class NodeblockState
  {
  protected:
    NodeblockMachine* machine;
    std::istream& input;
  public:
    NodeblockState(NodeblockMachine*);
    virtual ~NodeblockState();
    virtual NodeblockState* run() = 0;
  };
}

#endif