#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

/* Nodespec type_of_nodespec */

#define NODE_EXCEPTION -1
#define SIMPLE_NODE 0
#define RANGE_PLACEHOLDER 1
#define EMPTY_NODE 2

/* Nodespec type */

#define COPY_PLACEHOLDER_FULL 0
#define CUT_PLACEHOLDER_FULL 1
#define COPY_PLACEHOLDER_REF 2
#define CUT_PLACEHOLDER_REF 3
#define NONE 4

struct Nodespec{
  char type_of_nodespec, type;
  int holder_number, parenthesis, holder_start;
  std::string regex, errors;
};

/* Instancespec type */

#define INSTANCE_EXCEPTION -1
#define COPY_INSTANCE 0
#define CUT_INSTANCE 1

struct Instancespec{
  char type;
  int holder_number;
  std::string replacing_string, errors;
};


#endif // STRUCTS_H
