#include "normal_nodeblock_state.hpp"
#include "regex_escape_nodeblock_state.hpp"
#include "regex_nodeblock_state.hpp"
#include "unexpected_end_of_input_exception.hpp"

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
    this->output << ')';
    return new NormalNodeblockState(this->machine);
  }
  else if (x == '\\')
    return  new RegexEscapeNodeblockState(this->machine);
  else
  {
    this->output << x;
    return this;
  }
}
