#include "unexpected_end_of_input_exception.hpp"

const char* Exceptions::UnexpectedEndOfInputException::what() const throw()
{
  return "Unexpected end of input.";
}
