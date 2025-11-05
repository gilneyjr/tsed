#ifndef INVALID_CHARACTER_EXCEPTION_HPP
#define INVALID_CHARACTER_EXCEPTION_HPP

#include <exception>

namespace Exceptions
{
  class InvalidCharacterException: public std::exception
  {
  protected:
    char c;
  public:
    InvalidCharacterException(char);
    virtual const char* what() const throw();
  };
}

#endif
