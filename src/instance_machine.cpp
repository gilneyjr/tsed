#include "instance_machine.h"
#include <string>
#include <ctype.h>
#include <sstream>

#define NORMAL_STATE          0
#define NORMAL_ESCAPE_STATE   1
#define QUOTED_STATE          2
#define QUOTED_ESCAPE_STATE   3
#define NUMBERING_STATE       4

using namespace std;

InstanceMachine::InstanceMachine(string instance_name)
{
  state = NORMAL_STATE;
  position = 0;

  brackets_flag = 0;
  parsed_number = -1;
  quote_type = 0;
  delimiter_type = 0;

  input = instance_name;
}

InstanceMachine::~InstanceMachine()
{

}

Instancespec InstanceMachine::execute()
{
  input_size = input.length();

  errors = string();

  while(position < input_size)
  {
    switch(state)
    {
      case NORMAL_STATE: normal_flow();
      break;
      case NORMAL_ESCAPE_STATE: normal_flow_escape();
      break;
      case QUOTED_STATE: quoted_flow();
      break;
      case QUOTED_ESCAPE_STATE: quoted_flow_escape();
      break;
      case NUMBERING_STATE: numbering();
      break;
    }

    if(!errors.empty())
    {
      break;
    }
  }

  Instancespec instance_spec;

  if(!errors.empty())
  {
    instance_spec.type = NODE_EXCEPTION;
    instance_spec.errors = errors;
    return instance_spec;
  }

  instance_spec.replacing_string = output;
  instance_spec.holder_number = parsed_number;

  if(delimiter_type == '[')
    instance_spec.type = CUT_INSTANCE;
  else if(delimiter_type == '{')
    instance_spec.type = COPY_INSTANCE;

  return instance_spec;
}

void InstanceMachine::parse_error()
{
  stringstream error;
  error << "<program> does not know how interpret " << input << " at column "<< position << ".";
  errors = error.str();
}

void InstanceMachine::normal_flow()
{
  char current = input[position];

  if( ( isalnum(current) || current == '-' || current == '_' )  && brackets_flag == 1  )
  {
    output.push_back(current);
  }
  else if( ( current == '[' || current == '{' ) && brackets_flag == 0 )
  {
    delimiter_type = current;
    brackets_flag++;

    state = NUMBERING_STATE;
    number = string();
  }
  else if( ( current == ']' || current == '}' ) && brackets_flag == 1 )
  {
    if( delimiter_type == '{' && current == ']' )
      errors = "Unmatched '{'.";
    if( delimiter_type == '[' && current == '}' )
      errors = "Unmatched '['.";

    brackets_flag++;
  }
  else if( current == '[' || current == '{' )
  {
    errors = "You may open brackets just once.";
  }
  else if( ( current == ']' || current == '}' ) && brackets_flag == 0 )
  {
    errors = "You should open a bracket first.";
  }
  else if( ( current == ']' || current == '}' ) && brackets_flag == 2 )
  {
    errors = "You should close a bracket just once.";
  }
  else if( current == '"' || current == '\'' )
  {
     quote_type = current;
     state = QUOTED_STATE;
  }
  else if( current == '\\' )
  {
    state = NORMAL_ESCAPE_STATE;
  }
  else
  {
     parse_error();
  }

  if( errors.empty() ) position++;
}

void InstanceMachine::normal_flow_escape()
{
  char current = input[position];

  if( current == '(' ||  current == ')' ||  current == '^' ||
      current == '$' ||  current == '[' ||  current == ']' ||
      current == '?' ||  current == '*' )
  {
    output.push_back('\\');
    output.push_back(current);
    state = NORMAL_STATE;
  }
  else if( current != ' ')
  {
    output.push_back(current);
    state = NORMAL_STATE;
  }
  else
  {
    parse_error();
  }

  if( errors.empty() ) position++;
}

void InstanceMachine::quoted_flow()
{
  char current = input[position];

  if( current == '\\' )
  {
    state = QUOTED_ESCAPE_STATE;
  }
  else if( current == quote_type)
  {
    state = NORMAL_STATE;
  }
  else
  {
    output.push_back(current);
  }

  if( errors.empty() ) position++;
}

void InstanceMachine::quoted_flow_escape()
{
  char current = input[position];

  output.push_back(current);
  state = QUOTED_STATE;

  if( errors.empty() ) position++;
}

void InstanceMachine::numbering()
{
  char current = input[position];

  if( isdigit(current) )
  {
    number.push_back(current);
  }
  else if( current == ':' )
  {
    parsed_number = stoi(number);
    state = NORMAL_STATE;
  }
  else if( current == ']' || current == '}' || number.empty() )
  {
    // special case to permit [] and {}
    parsed_number = 0;
    position--;
    state = NORMAL_STATE;
  }
  else
  {
    errors = "You should separate the identifier by a colon.";
  }

  if( errors.empty() ) position++;
}
