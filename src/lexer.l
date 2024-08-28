%{
  #include <string> // string
  #include "parser.tab.h" // header genereted by yacc

  using namespace std;

  int yycolumn = 1; // Column counter

  // Directive executed at the beginning of each rule, after yytext and yyleng
  // Set lexem and update yycolumn with the token length
  #define YY_USER_ACTION \
    yylval.lexem = new string(yytext); \
    yycolumn += yyleng;

  #define YY_NO_UNPUT // Used to not define the yyunput function in order to suppress a warning

  extern int yyerror(const char *s); // Function defined in the yacc file
%}

DIGIT               [0-9]
NUMBER              {DIGIT}+
ALFANUM             [[:alnum:]-]
WILDCARD            \?
ANYSEQUENCE         \*
ESCAPED             \\.
DQSTRING            \"([^"\\]|\\.)*\"
SQSTRING            \'([^'\\]|\\.)*\'
OLD_REGEX           \/([^/\\]|\\+[^\\])+\/
REGEX               \/([^/]|\/\/)+\/
ALT_REGEX           \/([^/\\]|\\[^\\])+\/
NODEBLOCK           ({ALFANUM}|{WILDCARD}|{ANYSEQUENCE}|{ESCAPED}|{DQSTRING}|{SQSTRING}|{REGEX})+

%%

"<"                { return op; }
"<<"               { return op; }
">"                { return op; }
">>"               { return op; }
"$"                { return op; }  // is a sibling of (proper, right or left. imm or not
"$."               { return op; }  // immediate left sibling
"$,"               { return op; }  // immediate right sibling
"$.."              { return op; }  // left sibling
"$,,"              { return op; }  // right sibling
"<,"               { return op; }  // is the parent of first child
"<-"               { return op; }  // is the parent of last child
"<'"               { return op; }  // same as <-
">,"               { return op; }  // is the first child of
">-"               { return op; }  // is the last child of
">'"               { return op; }  // same as >-
"<:"               { return op; }
">:"               { return op; }
"<<,"              { return op; }  // is ancestor of leftmost descendant
"<<'"              { return op; }  // is ancestor of rightmost descendant
">>,"              { return op; }  // is leftmost descendant
">>'"              { return op; }  // is rightmost descendant
"<"{NUMBER}        { return op; }  // is the parent of n-th child
">"{NUMBER}        { return op; }  // is n-th child of
"<-"{NUMBER}       { return op; }  // is the parent of n-th child from r to l
">-"{NUMBER}       { return op; }  // is n-th child from right to left of
"."                { return op; }
","                { return op; }
".."               { return op; }
",,"               { return op; }
"<<:"              { return op; }
">>:"              { return op; }
"!<"               { return op; }
"!<<"              { return op; }
"!>"               { return op; }
"!>>"              { return op; }
"!$"               { return op; }  // is not a sibling of
"!$."              { return op; }  // not immediate left sibling //same
"!$,"              { return op; }  // not immediate right sibling
"!$.."             { return op; }  // not left sibling
"!$,,"             { return op; }  // not right sibling
"!<,"              { return op; }  // is not the parent of first child
"!<-"              { return op; }  // is not the parent of last child
"!<'"              { return op; }  // same as "!<-"
"!>,"              { return op; }  // is not the first child of
"!>-"              { return op; }  // is not the last child of
"!>'"              { return op; }  // same as "!>-"
"!<:"              { return op; }
"!>:"              { return op; }
"!<<,"             { return op; }  // is not ancestor of leftmost descendant
"!<<'"             { return op; }  // is not ancestor of rightmost descendant
"!>>,"             { return op; }  // is not leftmost descendant
"!>>'"             { return op; }  // is not rightmost descendant
"!<"{NUMBER}       { return op; }  // is the parent of n-th child
"!>"{NUMBER}       { return op; }  // is n-th child of
"!<-"{NUMBER}      { return op; }  // is the parent of n-th child from r to l
"!>-"{NUMBER}      { return op; }  // is n-th child from right to left of
"!."               { return op; }
"!,"               { return op; }
"!.."              { return op; }
"!,,"              { return op; }
"!<<:"             { return op; }
"!>>:"             { return op; }
"="                { return op; }
"~"                { return op; }

{NODEBLOCK}                                             { return nodename; }  // No placeholder
{NODEBLOCK}?"["({NUMBER}\:)?{NODEBLOCK}?"]"{NODEBLOCK}? { return nodename; }  // Cut declaration/backreference placeholder with/without explicit number
{NODEBLOCK}?"{"{NUMBER}\:{NODEBLOCK}?"}"{NODEBLOCK}?    { return nodename; }  // Copy declaration/backreference placeholder with explicit number
"["({NUMBER}\:)?\.\.\."]"                               { return nodename; }  // Cut subtree range placeholder with/without explicit number
"{"{NUMBER}\:\.\.\."}"                                  { return nodename; }  // Copy subtree range placeholder with explicit number

"&"                   { return terminal_and; }
"|"                   { return terminal_or; }
"!"                   { return terminal_not; }
"#"                   { return end_marker; }
"("                   { return lpar; }
")"                   { return rpar; }
\/\/.*                ; // TODO: Verify what is this for (Is this for comments?)

"==>"                 { return turnsto; }

" "                   ; // Spaces allowed for readability
\n|\r|\n\r|\r\n       ; // New line // TODO: Verify if new line should be allowed
.                     { yyerror("lexical error: unexpected character"); }

%%

int yywrap() { return 1; }