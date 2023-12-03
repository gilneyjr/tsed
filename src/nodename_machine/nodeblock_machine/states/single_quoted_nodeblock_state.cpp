#include "single_quoted_escape_nodeblock_state.hpp"
#include "single_quoted_nodeblock_state.hpp"

Nodename::Nodeblock::SingleQuotedNodeblockState::SingleQuotedNodeblockState(
    Nodename::Nodeblock::NodeblockMachine* machine):
    Nodename::Nodeblock::NodeblockState(machine) {}

Nodename::Nodeblock::SingleQuotedNodeblockState::~SingleQuotedNodeblockState() {}

Nodename::Nodeblock::NodeblockState* Nodename::Nodeblock::SingleQuotedNodeblockState::run()
{
    std::istream& in = *(this->machine->getInputStream());
    std::ostream& out = *(this->machine->getOutputStream());

    if (in.eof())
        /* TODO: throw new Exception("Fim de stream inesperado.") */;
    
    char x;
    in >> x;

    if (true /* x in <special> - {\, "} */)
        out << "\\" << x;
    else if (true /* x in Sigma - ( { " } U <special> ) */)
        out << x;
    else if (x == '\\')
        return new SingleQuotedEscapeNodeblockState(this->machine);
    else
        /* TODO: throw new Exception("caractere inválido.") */;
    
    return this;
}