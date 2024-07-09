#include "nodeblock_machine.hpp"
#include "begin_nodeblock_state.hpp"

Nodename::Nodeblock::NodeblockMachine::NodeblockMachine(std::istream& input)
  : input(input)
{
  this->state = new Nodename::Nodeblock::BeginNodeblockState(this);
  this->finished = false;
  this->undetermined = false;
  this->regex = "";
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
  while (!this->finished && this->state != nullptr) 
  {
    NodeblockState* nextState = this->state->run();

    if (this->state != nullptr && this->state != nextState) 
    {
      delete this->state;
      this->state = nextState;
    }
  }

  return NodeblockResult(this->undetermined, this->regex);
}

std::istream& Nodename::Nodeblock::NodeblockMachine::getInputStream() 
{
  return this->input;
}

void Nodename::Nodeblock::NodeblockMachine::setUndetermined(bool undetermined)
{
  this->undetermined = undetermined;
}

void Nodename::Nodeblock::NodeblockMachine::appendToOutput(std::string input)
{
  this->regex += input;
}

void Nodename::Nodeblock::NodeblockMachine::appendToOutput(char input)
{
  this->regex += input;
}