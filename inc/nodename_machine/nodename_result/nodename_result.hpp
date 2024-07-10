#ifndef NODENAME_RESULT_HPP
#define NODENAME_RESULT_HPP

#include <string>

#include "def_or_ref.hpp"
#include "nodename_result_type.hpp"
#include "placeholder.hpp"

namespace Nodename::NodenameResult
{
  enum class NodenameResultType;
  enum class Placeholder;
  enum class DefOrRef;

  struct NodenameResult
  {
    NodenameResultType type;
    Placeholder placeholder;
    int placeholderNumber;
    bool undetermined; // true, when nodename has ANY, WILDCARD or REGEX inside it; false, otherwise.
    bool freeOfContext; // true, when nodename doesn't have specified left or right contexts; false, otherwise.
    DefOrRef defOrRef; // The placeholder is a definition, a reference or neither of them.
    std::string regex;
    
    // TODO: Verificar se os atributos abaixo precisam estar no resultado
    bool validAsLNodename; // Depends on context 
    bool validAsRNodename; // !undetermined && freeOfContext && defOrRef != DEFINITION

    NodenameResult() // TODO: mover isso para um .cpp depois ?
    {
      this->type = NodenameResultType::SIMPLE_NODE;
      this->placeholder = Placeholder::NONE;
      this->placeholderNumber = 0;
      this->undetermined = false,
      this->freeOfContext = true;
      this->defOrRef = DefOrRef::NONE;
      this->validAsLNodename = true;
      this->validAsRNodename = true;
      std::string regex = nullptr;
    }
  };
}

#endif
