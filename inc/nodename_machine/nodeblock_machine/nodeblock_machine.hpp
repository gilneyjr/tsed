#ifndef NODEBLOCK_MACHINE_HPP
#define NODEBLOCK_MACHINE_HPP

#include <iostream>
#include "nodeblock_state.hpp"

namespace Nodename::Nodeblock
{
  class NodeblockState;
  class NodeblockMachine
  {
  private:
    bool finished;
    NodeblockState* state;
    std::istream& input;
    std::ostream& output;
  public:
    NodeblockMachine(std::istream&, std::ostream&);
    ~NodeblockMachine();
    void finish();
    void run();
    std::istream& getInputStream();
    std::ostream& getOutputStream();
  };
}

#endif