#include "regex_nodeblock_state.hpp"
#include "nodeblock_machine.hpp"
#include "normal_nodeblock_state.hpp"

Nodename::Nodeblock::RegexNodeblockState::RegexNodeblockState(
  Nodename::Nodeblock::NodeblockMachine* machine): 
  Nodename::Nodeblock::NodeblockState(machine) {} 

Nodename::Nodeblock::RegexNodeblockState::~RegexNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::RegexNodeblockState::run()
{
    std::istream& in = *(this->machine->getInputStream());
    std::ostream& out = *(this->machine->getOutputStream());
    
    if (in.eof())
        /* TODO: throw new Exception("fim de stream inesperado.") */;
    
    char x;
    in >> x;

    if (x == '/')
    {
        out << ")";
        return new NormalNodeblockState(this->machine);
    }
    else if (x == '\\')
        return  new RegexEscapeNodeblockState(this->machine);
    else
    {
        out << x;
        return this;
    }
}