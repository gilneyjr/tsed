#include "double_quoted_escape_nodeblock_state.hpp"
#include "double_quoted_nodeblock_state.hpp"
#include "normal_nodeblock_state.hpp"
#include "unexpected_end_of_input_exception.hpp"

Nodename::Nodeblock::DoubleQuotedNodeblockState::DoubleQuotedNodeblockState(
  Nodename::Nodeblock::NodeblockMachine* machine):
  Nodename::Nodeblock::NodeblockState(machine) {}

Nodename::Nodeblock::DoubleQuotedNodeblockState::~DoubleQuotedNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::DoubleQuotedNodeblockState::run()
{
  char x;
  this->input >> x;
  
  if (this->input.eof())
    throw Exceptions::UnexpectedEndOfInputException();

  if (x == '"')
  {
    this->machine->appendToOutput(')');
    return new NormalNodeblockState(this->machine);
  }
  else if (x == '\\')
    return new DoubleQuotedEscapeNodeblockState(this->machine);
  else if (std::isalnum(x))
  {
    this->machine->appendToOutput(x);
    return this;
  }
  else 
  {
    this->machine->appendToOutput("\\" + x);
    return this;
  }
}
