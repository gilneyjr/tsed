#include "nodeblock_machine.hpp"
#include "begin_nodeblock_state.hpp"

Nodename::Nodeblock::NodeblockMachine::NodeblockMachine(std::istream& input)
  : input(input)
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

Nodename::Nodeblock::NodeblockResult Nodename::Nodeblock::NodeblockMachine::run() 
{
  this->result = NodeblockResult();

  while (!this->finished && this->state != nullptr) 
  {
    NodeblockState* nextState = this->state->run();

    if (this->state != nullptr && this->state != nextState) 
    {
      delete this->state;
      this->state = nextState;
    }
  }

  return this->result;
}

std::istream& Nodename::Nodeblock::NodeblockMachine::getInputStream() 
{
  return this->input;
}

void Nodename::Nodeblock::NodeblockMachine::setUndetermined(bool undetermined)
{
  this->result.undetermined = undetermined;
}

void Nodename::Nodeblock::NodeblockMachine::appendToOutput(std::string input)
{
  this->result.regex += input;
}

void Nodename::Nodeblock::NodeblockMachine::appendToOutput(char input)
{
  this->result.regex += input;
}