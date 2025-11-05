#include "double-quoted-escape-nodeblock-state.hpp"
#include "double-quoted-nodeblock-state.hpp"
#include "normal-nodeblock-state.hpp"
#include "unexpected-end-of-input-exception.hpp"

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
    this->machine->appendToOutput('\\');
    this->machine->appendToOutput(x);
    return this;
  }
}
