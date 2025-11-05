#include "regex-escape-nodeblock-state.hpp"
#include "regex-nodeblock-state.hpp"
#include "unexpected-end-of-input-exception.hpp"

Nodename::Nodeblock::RegexEscapeNodeblockState::RegexEscapeNodeblockState(
  Nodename::Nodeblock::NodeblockMachine* machine): 
  Nodename::Nodeblock::NodeblockState(machine) {} 

Nodename::Nodeblock::RegexEscapeNodeblockState::~RegexEscapeNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::RegexEscapeNodeblockState::run()
{
  char x;
  this->input >> x;

  if (this->input.eof())
    throw Exceptions::UnexpectedEndOfInputException();

  if (x == '/')
    this->machine->appendToOutput(x);
  else
  {
    this->machine->appendToOutput('\\');
    this->machine->appendToOutput(x);
  }

  return new RegexNodeblockState(this->machine);
}