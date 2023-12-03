#include "double_quoted_escape_nodeblock_state.hpp"
#include "double_quoted_nodeblock_state.hpp"
#include "normal_nodeblock_state.hpp"

Nodename::Nodeblock::DoubleQuotedNodeblockState::DoubleQuotedNodeblockState(
  Nodename::Nodeblock::NodeblockMachine* machine):
  Nodename::Nodeblock::NodeblockState(machine) {}

Nodename::Nodeblock::DoubleQuotedNodeblockState::~DoubleQuotedNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::DoubleQuotedNodeblockState::run()
{
  if (this->input.eof())
    throw "Unexpected end of input."; // TODO: Criar uma excessão para isso
  
  char x;
  this->input >> x;

  if (x == '"')
  {
    this->output << ')';
    return new NormalNodeblockState(this->machine);
  }
  else if (x == '\\')
    return new DoubleQuotedEscapeNodeblockState(this->machine);
  else
  {
    this->output << x;
    return this;
  }
}