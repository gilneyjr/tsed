#include "normal_nodeblock_state.hpp"
#include "regex_escape_nodeblock_state.hpp"
#include "regex_nodeblock_state.hpp"

Nodename::Nodeblock::RegexNodeblockState::RegexNodeblockState(
  Nodename::Nodeblock::NodeblockMachine* machine): 
  Nodename::Nodeblock::NodeblockState(machine) {} 

Nodename::Nodeblock::RegexNodeblockState::~RegexNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::RegexNodeblockState::run()
{   
  char x;
  this->input >> x;
  
  if (this->input.eof())
    throw "Unexpected end of input."; // TODO: Criar uma excessão para isso

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
