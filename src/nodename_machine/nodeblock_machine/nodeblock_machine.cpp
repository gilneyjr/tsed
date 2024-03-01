#include "nodeblock_machine.hpp"
#include "begin_nodeblock_state.hpp"

Nodename::Nodeblock::NodeblockMachine::NodeblockMachine(std::istream& input, std::ostream& output)
  : input(input), output(output)
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

std::istream& Nodename::Nodeblock::NodeblockMachine::getInputStream() 
{
  return this->input;
}

std::ostream& Nodename::Nodeblock::NodeblockMachine::getOutputStream()
{
  return this->output;
}

// TODO: implementar quais caracteres são especiais
// TODO: pensar se vou deixar esse método aqui ou vou passar para uma classe de utils
bool Nodename::Nodeblock::NodeblockMachine::isEscapableChar(char c)
{
  return c == '\\';
}