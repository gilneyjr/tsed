%{
  #include "parser.tab.h" // header genereted by yacc
  
  #include <string> // string

  using namespace std;
  
  int lineNumber = 1;       // Line counter
  int columnNumber = 1;     // Column counter
  void incrementColumns();  // Count a new line
  void carriageReturn();    // Count the number of columns read

  extern int yyerror(const char *s); // Function defined in the yacc file

  #define YY_NO_UNPUT // Used to not define the yyunput function in order to suppress a warning
%}

ALFANUM             [[:alnum:]-]
WILDCARD            \?
ANYSEQUENCE         \*
ESCAPED             \\.
DQSTRING            \"([^"\\]|\\.)*\"
SQSTRING            \'([^'\\]|\\.)*\'
REGEX               \/([^/]|\/\/)+\/
NODEBLOCK           ({ALFANUM}|{WILDCARD}|{ANYSEQUENCE}|{ESCAPED}|{DQSTRING}|{SQSTRING}|{REGEX})+

%%

"<"                   { incrementColumns(); yylval.output = new string(yytext); return imdoms; }

{NODEBLOCK}           { incrementColumns(); yylval.output = new string(yytext); return nodename; }

" "                   { incrementColumns(); } // Spaces allowed for readability
\n|\r|\n\r|\r\n       { carriageReturn(); }   // New line
.                     { incrementColumns(); yyerror("lexical error: unexpected character"); }

%%

void incrementColumns()
{
  lineNumber += yyleng;
}

void carriageReturn()
{
  lineNumber += yyleng;
  columnNumber = 1;
}

int yywrap() { return 1; }