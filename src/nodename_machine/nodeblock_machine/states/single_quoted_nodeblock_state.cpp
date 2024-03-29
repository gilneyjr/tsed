#include "normal_nodeblock_state.hpp"
#include "single_quoted_escape_nodeblock_state.hpp"
#include "single_quoted_nodeblock_state.hpp"

Nodename::Nodeblock::SingleQuotedNodeblockState::SingleQuotedNodeblockState(
  Nodename::Nodeblock::NodeblockMachine* machine):
  Nodename::Nodeblock::NodeblockState(machine) {}

Nodename::Nodeblock::SingleQuotedNodeblockState::~SingleQuotedNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::SingleQuotedNodeblockState::run()
{
  char x;
  this->input >> x;
  
  if (this->input.eof())
    throw "Unexpected end of input."; // TODO: Criar uma excessão para isso

  if (x == '\'')
  {
    this->output << ')';
    return new NormalNodeblockState(this->machine);
  }
  else if (x == '\\')
    return new SingleQuotedEscapeNodeblockState(this->machine);
  else if (std::isalnum(x))
  {
    this->output << x;
    return this;
  }
  else 
  {
    this->output << '\\' << x;
    return this;
  }
}
