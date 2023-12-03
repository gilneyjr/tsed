#include "single_quoted_escape_nodeblock_state.hpp"
#include "single_quoted_nodeblock_state.hpp"

Nodename::Nodeblock::SingleQuotedEscapeNodeblockState::SingleQuotedEscapeNodeblockState(
    Nodename::Nodeblock::NodeblockMachine* machine):
    Nodename::Nodeblock::NodeblockState(machine) {}

Nodename::Nodeblock::SingleQuotedEscapeNodeblockState::~SingleQuotedEscapeNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::SingleQuotedEscapeNodeblockState::run()
{
    std::istream& in = *(this->machine->getInputStream());
    std::ostream& out = *(this->machine->getOutputStream());

    if (in.eof())
        /* TODO: throw new Exception("fim de stream inválido.") */;
    
    char x;
    in >> x;

    if (true /* x in <special> */)
        out << "\\" << x;
    else
        out << x;
    return new SingleQuotedNodeblockState(this->machine);
}