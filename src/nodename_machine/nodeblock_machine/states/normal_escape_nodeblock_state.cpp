#include "normal_escape_nodeblock_state.hpp"
#include "normal_nodeblock_state.hpp"

Nodename::Nodeblock::NormalEscapeNodeblockState::NormalEscapeNodeblockState(
  Nodename::Nodeblock::NodeblockMachine* machine):
  Nodename::Nodeblock::NodeblockState(machine) {}

Nodename::Nodeblock::NormalEscapeNodeblockState::~NormalEscapeNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::NormalEscapeNodeblockState::run()
{
  if (this->input.eof())
    throw "Unexpected end of input."; // TODO: Criar uma excessão para isso

  char x;
  this->input >> x;

  if (machine->isEscapableChar(x))
    this->output << '\\' << x;
  else
    this->output << x;

  return new NormalNodeblockState(this->machine);
}