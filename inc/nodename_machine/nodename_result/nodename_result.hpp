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
    // TODO: Revisar maneira com que esses valores foram obtidos
    NodenameResultType type; //                                                         [OK]
    Placeholder placeholder; //                                                         [OK]
    int placeholderNumber; //                                                           [OK]
    bool undetermined; // true quando não possui ANY, WILDCARD ou REGEX                 [  ]
    bool freeOfContext; // true quando não tiver left/right context especificados       [OK]
    DefOrRef defOrRef; // O placeholder é uma definição ou uma referência               [  ]
    bool validAsRNodename; // !undetermined && freeOfContext && defOrRef != DEFINITION  [  ]
    bool validAsLNodename; // Depende do contexto                                       [  ]
    std::string regex; //                                                               [  ]

    NodenameResult(
      NodenameResultType type,
      Placeholder placeholder,
      int placeholderNumber,
      bool undetermined,
      bool freeOfContext,
      DefOrRef defOrRef,
      bool validAsRNodename,
      bool validAsLNodename,
      std::string regex
    ) 
    {
      this->type = type;
      this->placeholder = placeholder;
      this->placeholderNumber = placeholderNumber;
      this->undetermined = undetermined;
      this->freeOfContext = freeOfContext;
      this->defOrRef = defOrRef;
      this->validAsRNodename = validAsRNodename;
      this->validAsLNodename = validAsLNodename;
      this->regex = regex;
    }
  };
}

#endif
