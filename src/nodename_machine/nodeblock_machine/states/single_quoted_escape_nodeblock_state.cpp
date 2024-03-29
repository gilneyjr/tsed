#include "single_quoted_escape_nodeblock_state.hpp"
#include "single_quoted_nodeblock_state.hpp"

Nodename::Nodeblock::SingleQuotedEscapeNodeblockState::SingleQuotedEscapeNodeblockState(
  Nodename::Nodeblock::NodeblockMachine* machine):
  Nodename::Nodeblock::NodeblockState(machine) {}

Nodename::Nodeblock::SingleQuotedEscapeNodeblockState::~SingleQuotedEscapeNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::SingleQuotedEscapeNodeblockState::run()
{
  char x;
  this->input >> x;
  
  if (this->input.eof())
    throw "Unexpected end of input."; // TODO: Criar uma excessão para isso

  if (!std::isalnum(x)) 
  {
    this->output << '\\' << x;
    return new SingleQuotedNodeblockState(this->machine);
  }
  else
    throw "Alfanumeric characters are not escapable inside strings."; // TODO: Criar uma excessão para isso
}
