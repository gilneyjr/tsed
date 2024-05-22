#include "regex_escape_nodeblock_state.hpp"
#include "regex_nodeblock_state.hpp"
#include "unexpected_end_of_input_exception.hpp"

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
    this->output << x;
  else
    this->output << '\\' << x;

  return new RegexNodeblockState(this->machine);
}