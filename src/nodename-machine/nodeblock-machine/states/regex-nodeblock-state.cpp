#include "normal-nodeblock-state.hpp"
#include "regex-escape-nodeblock-state.hpp"
#include "regex-nodeblock-state.hpp"
#include "unexpected-end-of-input-exception.hpp"

Nodename::Nodeblock::RegexNodeblockState::RegexNodeblockState(
  Nodename::Nodeblock::NodeblockMachine* machine): 
  Nodename::Nodeblock::NodeblockState(machine) {} 

Nodename::Nodeblock::RegexNodeblockState::~RegexNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::RegexNodeblockState::run()
{
  char x;
  this->input >> x;
  
  if (this->input.eof())
    throw Exceptions::UnexpectedEndOfInputException();

  if (x == '/')
  {
    this->machine->appendToOutput(')');
    return new NormalNodeblockState(this->machine);
  }
  else if (x == '\\')
    return  new RegexEscapeNodeblockState(this->machine);
  else if (x == '(')
  {
    this->machine->appendToOutput(x);
    this->machine->appendToOutput('?');
    this->machine->appendToOutput(':');
    return this;
  }
  else
  {
    this->machine->appendToOutput(x);
    return this;
  }
}
