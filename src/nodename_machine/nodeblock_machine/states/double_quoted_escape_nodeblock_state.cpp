#include "double_quoted_escape_nodeblock_state.hpp"
#include "double_quoted_nodeblock_state.hpp"

Nodename::Nodeblock::DoubleQuotedEscapeNodeblockState::DoubleQuotedEscapeNodeblockState(
  Nodename::Nodeblock::NodeblockMachine* machine):
  Nodename::Nodeblock::NodeblockState(machine) {}

Nodename::Nodeblock::DoubleQuotedEscapeNodeblockState::~DoubleQuotedEscapeNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::DoubleQuotedEscapeNodeblockState::run()
{
  char x;
  this->input >> x;

  if (this->input.eof())
    throw "Unexpected end of input."; // TODO: Criar uma excessão para isso
  
  if (machine->isEscapableChar(x))
    this->output << '\\' << x;
  else
    this->output << x;

  return new DoubleQuotedNodeblockState(this->machine);
}