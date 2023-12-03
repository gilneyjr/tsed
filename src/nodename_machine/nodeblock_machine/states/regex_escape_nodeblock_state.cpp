#include "regex_escape_nodeblock_state.hpp"
#include "regex_nodeblock_state.hpp"

Nodename::Nodeblock::RegexEscapeNodeblockState::RegexEscapeNodeblockState(
  Nodename::Nodeblock::NodeblockMachine* machine): 
  Nodename::Nodeblock::NodeblockState(machine) {} 

Nodename::Nodeblock::RegexEscapeNodeblockState::~RegexEscapeNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::RegexEscapeNodeblockState::run()
{
  if (this->input.eof())
    throw "Unexpected end of input."; // TODO: Criar uma excessão para isso
  
  char x;
  this->input >> x;

  if (machine->isEscapableChar(x))
    this->output << '\\' << x;
  else
    this->output << x;

  return new RegexNodeblockState(this->machine);
}