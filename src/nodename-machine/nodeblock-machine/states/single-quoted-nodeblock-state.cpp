#include "normal-nodeblock-state.hpp"
#include "single-quoted-escape-nodeblock-state.hpp"
#include "single-quoted-nodeblock-state.hpp"
#include "unexpected-end-of-input-exception.hpp"

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
    this->machine->appendToOutput('\\');
    this->machine->appendToOutput(x);
    return this;
  }
}
