#include "normal-escape-nodeblock-state.hpp"
#include "normal-nodeblock-state.hpp"
#include "unexpected-end-of-input-exception.hpp"

Nodename::Nodeblock::NormalEscapeNodeblockState::NormalEscapeNodeblockState(
  Nodename::Nodeblock::NodeblockMachine* machine):
  Nodename::Nodeblock::NodeblockState(machine) {}

Nodename::Nodeblock::NormalEscapeNodeblockState::~NormalEscapeNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::NormalEscapeNodeblockState::run()
{
  char x;
  this->input >> x;
  
  if (this->input.eof())
    throw Exceptions::UnexpectedEndOfInputException();

  if (!std::isalnum(x))
  {
    this->machine->appendToOutput('\\');
    this->machine->appendToOutput(x);
    return new NormalNodeblockState(this->machine);
  }
  else
    throw "Alfanumeric characters are not escapable in normal mode."; // TODO: create an exception for this later
}
