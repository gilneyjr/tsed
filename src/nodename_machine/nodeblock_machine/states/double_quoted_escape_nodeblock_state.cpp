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

  if (!std::isalnum(x)) 
  {
    this->output << '\\' << x;
    return new DoubleQuotedNodeblockState(this->machine);
  }
  else
    throw "Alfanumeric characters are not escapable inside strings."; // TODO: Criar uma excessão para isso
}