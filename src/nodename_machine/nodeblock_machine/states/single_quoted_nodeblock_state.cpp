#include "normal_nodeblock_state.hpp"
#include "single_quoted_escape_nodeblock_state.hpp"
#include "single_quoted_nodeblock_state.hpp"
#include "unexpected_end_of_input_exception.hpp"

Nodename::Nodeblock::SingleQuotedNodeblockState::SingleQuotedNodeblockState(
  Nodename::Nodeblock::NodeblockMachine* machine):
  Nodename::Nodeblock::NodeblockState(machine) {}

Nodename::Nodeblock::SingleQuotedNodeblockState::~SingleQuotedNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::SingleQuotedNodeblockState::run()
{
  char x;
  this->input >> x;
  
  if (this->input.eof())
    throw Exceptions::UnexpectedEndOfInputException();

  if (x == '\'')
  {
    this->machine->appendToOutput(')');
    return new NormalNodeblockState(this->machine);
  }
  else if (x == '\\')
    return new SingleQuotedEscapeNodeblockState(this->machine);
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
