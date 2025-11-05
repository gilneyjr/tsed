#include "single-quoted-escape-nodeblock-state.hpp"
#include "single-quoted-nodeblock-state.hpp"
#include "unexpected-end-of-input-exception.hpp"

Nodename::Nodeblock::SingleQuotedEscapeNodeblockState::SingleQuotedEscapeNodeblockState(
  Nodename::Nodeblock::NodeblockMachine* machine):
  Nodename::Nodeblock::NodeblockState(machine) {}

Nodename::Nodeblock::SingleQuotedEscapeNodeblockState::~SingleQuotedEscapeNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::SingleQuotedEscapeNodeblockState::run()
{
  char x;
  this->input >> x;
  
  if (this->input.eof())
    throw Exceptions::UnexpectedEndOfInputException();

  if (!std::isalnum(x)) 
  {
    this->machine->appendToOutput('\\');
    this->machine->appendToOutput(x);
    return new SingleQuotedNodeblockState(this->machine);
  }
  else
    throw "Alfanumeric characters are not escapable inside strings."; // TODO: create an exception for this later
}
