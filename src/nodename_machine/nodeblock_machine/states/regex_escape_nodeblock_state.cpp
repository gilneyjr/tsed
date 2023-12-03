#include "regex_escape_nodeblock_state.hpp"
#include "regex_nodeblock_state.hpp"

Nodename::Nodeblock::RegexEscapeNodeblockState::RegexEscapeNodeblockState(
  Nodename::Nodeblock::NodeblockMachine* machine): 
  Nodename::Nodeblock::NodeblockState(machine) {} 

Nodename::Nodeblock::RegexEscapeNodeblockState::~RegexEscapeNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::RegexEscapeNodeblockState::run()
{
  std::istream& in = *(this->machine->getInputStream());
  std::ostream& out = *(this->machine->getOutputStream());
  
  if (in.eof())
    /* TODO: throw new Exception("fim de stream inesperado.") */;
  
  char x;
  in >> x;
  out << x;
  return new RegexNodeblockState(this->machine);
}