#include "invalid_character_exception.hpp"
#include <string>

Exceptions::InvalidCharacterException::InvalidCharacterException(char c): c(c) {}

const char* Exceptions::InvalidCharacterException::what() const throw()
{
  return ("Invalid character: '" + std::string(1, this->c) + "'.").c_str();
}
