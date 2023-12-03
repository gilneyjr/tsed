#include "nodeblock_machine.hpp"
#include "begin_nodeblock_state.hpp"

Nodename::Nodeblock::NodeblockMachine::NodeblockMachine()
{
  this->state = new Nodename::Nodeblock::BeginNodeblockState(this);
  this->finished = false;
}

Nodename::Nodeblock::NodeblockMachine::~NodeblockMachine()
{
  delete this->state;
}

void Nodename::Nodeblock::NodeblockMachine::finish()
{
  this->finished = true;
}

void Nodename::Nodeblock::NodeblockMachine::run() 
{
  while (!this->finished && this->state != nullptr) 
  {
    NodeblockState* nextState = this->state->run();
    if (this->state != nullptr && this->state != nextState) 
    {
      delete this->state;
      this->state = nextState;
    }
  }
}

std::istream* Nodename::Nodeblock::NodeblockMachine::getInputStream() 
{
  return this->input;
}

std::ostream* Nodename::Nodeblock::NodeblockMachine::getOutputStream()
{
  return this->output;
}