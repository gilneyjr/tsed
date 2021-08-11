%{
	#include <string>
	#include "y.tab.h"
	int nchar, nline, nword;
	#define ACCOUNTABLE nword++;nchar+=yyleng;

%}

DIGIT				[0-9]
NUMBER				{DIGIT}+
ALFANUM             [[:alnum:]-]
WILDCARD            \?
ANYSEQUENCE         \*
ESCAPED             \\.
DQSTRING            \"([^"\\]|\\.)*\"
SQSTRING            \'([^'\\]|\\.)*\'
OLD_REGEX           \/([^/\\]|\\+[^\\])+\/
REGEX               \/([^/]|\/\/)+\/
ALT_REGEX           \/([^/\\]|\\[^\\])+\/
NODEBLOCK          	({ALFANUM}|{WILDCARD}|{ANYSEQUENCE}|{ESCAPED}|{DQSTRING}|{SQSTRING}|{REGEX})+

%%
"<" 	{ACCOUNTABLE return imdoms;}
"<<" 	{ACCOUNTABLE return doms;}
">" 	{ACCOUNTABLE return imdomted;}
">>" 	{ACCOUNTABLE return domted;}
"$" 	{ACCOUNTABLE return siblproper;}  // is a sibling of (proper, right or left. imm or not
"$." 	{ACCOUNTABLE return imlsibl;}    // immediate left sibling
"$," 	{ACCOUNTABLE return imrsibl;}    // immediate right sibling
"$.." 	{ACCOUNTABLE return lsibl;}    // left sibling
"$,," 	{ACCOUNTABLE return rsibl;}    // right sibling

"<," 	{ACCOUNTABLE return fstchildpar;} // is the parent of first child
"<-" 	{ACCOUNTABLE return lastchildpar;} // is the parent of last child
"<'" 	{ACCOUNTABLE return lastchildpar;} // same as <-
">," 	{ACCOUNTABLE return fstchild;} // is the first child of
">-" 	{ACCOUNTABLE return lastchild;} // is the last child of
">'" 	{ACCOUNTABLE return lastchild;} // same as >-

"<:" 	{ACCOUNTABLE return onlychildpar;}
">:" 	{ACCOUNTABLE return onlychild;}

"<<," 	{ACCOUNTABLE return lmanc;}   // is ancestor of leftmost descendant
"<<'" 	{ACCOUNTABLE return rmanc ;}  // is ancestor of rightmost descendant
">>," 	{ACCOUNTABLE return lmdesc;}  // is leftmost descendant
">>'" 	{ACCOUNTABLE return rmdesc;}  // is rightmost descendant

"<"{NUMBER} 	{ACCOUNTABLE return nthparent;} // is the parent of n-th child
">"{NUMBER} 	{ACCOUNTABLE return nthchild;} // is n-th child of
"<-"{NUMBER} 	{ACCOUNTABLE return nthparent_end;} // is the parent of n-th child from r to l
">-"{NUMBER} 	{ACCOUNTABLE return nthchild_end;} // is n-th child from right to left of

"." 	{ACCOUNTABLE return imprec;}
"," 	{ACCOUNTABLE return imsucc;}
".." 	{ACCOUNTABLE return prec;}
",," 	{ACCOUNTABLE return succ;}

"<<:" 	{ACCOUNTABLE return singdescpat;}
">>:" 	{ACCOUNTABLE return singascpath;}

"!<" 	{ACCOUNTABLE return nimdoms;}
"!<<" 	{ACCOUNTABLE return ndoms;}
"!>" 	{ACCOUNTABLE return nimdomted;}
"!>>" 	{ACCOUNTABLE return ndomted;}
"!$" 	{ACCOUNTABLE return nsiblproper;}  // is not a sibling of
"!$." 	{ACCOUNTABLE return nimlsibl;}    // not immediate left sibling //same
"!$," 	{ACCOUNTABLE return nimrsibl;}    // not immediate right sibling
"!$.." 	{ACCOUNTABLE return nlsibl;}    // not left sibling
"!$,," 	{ACCOUNTABLE return nrsibl;}    // not right sibling

"!<," 	{ACCOUNTABLE return nfstchildpar;} // is not the parent of first child
"!<-" 	{ACCOUNTABLE return nlastchildpar;} // is not the parent of last child
"!<'" 	{ACCOUNTABLE return nlastchildpar;} // same as "!<-"
"!>," 	{ACCOUNTABLE return nfstchild;} // is not the first child of
"!>-" 	{ACCOUNTABLE return nlastchild;} // is not the last child of
"!>'" 	{ACCOUNTABLE return nlastchild;} // same as "!>-"

"!<:" 	{ACCOUNTABLE return nonlychildpar;}
"!>:" 	{ACCOUNTABLE return nonlychild;}

"!<<," 		{ACCOUNTABLE return nlmanc;}   // is not ancestor of leftmost descendant
"!<<'" 		{ACCOUNTABLE return nrmanc ;}  // is not ancestor of rightmost descendant
"!>>," 		{ACCOUNTABLE return nlmdesc;}  // is not leftmost descendant
"!>>'" 		{ACCOUNTABLE return nrmdesc;}  // is not rightmost descendant
"!<"{NUMBER} 	{ACCOUNTABLE return nnthparent;} // is the parent of n-th child
"!>"{NUMBER}	{ACCOUNTABLE return nnthchild;} // is n-th child of
"!<-"{NUMBER} 	{ACCOUNTABLE return nnthparent_end;} // is the parent of n-th child from r to l
"!>-"{NUMBER} 	{ACCOUNTABLE return nnthchild_end;} // is n-th child from right to left of
"!." 		{ACCOUNTABLE return nimprec;}
"!," 		{ACCOUNTABLE return nimsucc;}
"!.." 		{ACCOUNTABLE return nprec;}
"!,," 		{ACCOUNTABLE return nsucc;}
"!<<:" 		{ACCOUNTABLE return nsingdescpat;}
"!>>:" 		{ACCOUNTABLE return nsingascpath;}

"=" 		{ACCOUNTABLE return EQ;}
"~" 		{ACCOUNTABLE return HOMON;}

{NODEBLOCK}                                                   {ACCOUNTABLE return nodename;}

{NODEBLOCK}?"["[[:blank:]]*"]"{NODEBLOCK}?                    {ACCOUNTABLE return nodename;}

{NODEBLOCK}?"{"({NUMBER}\:)?[[:blank:]]*"}"{NODEBLOCK}?       {ACCOUNTABLE return nodename;}
{NODEBLOCK}?"["({NUMBER}\:)?[[:blank:]]*"]"{NODEBLOCK}?       {ACCOUNTABLE return nodename;} // number opt??

{NODEBLOCK}?"["({NUMBER}\:)?{NODEBLOCK}"]"{NODEBLOCK}?        {ACCOUNTABLE return nodename;}
{NODEBLOCK}?"{"({NUMBER}\:)?{NODEBLOCK}"}"{NODEBLOCK}?        {ACCOUNTABLE return nodename;}

{NODEBLOCK}?"{"({NUMBER}\:)?[[:blank:]]*\.\.\.[[:blank:]]*"}"{NODEBLOCK}?     {ACCOUNTABLE return nodename; }
{NODEBLOCK}?"["({NUMBER}\:)?[[:blank:]]*\.\.\.[[:blank:]]*"]"{NODEBLOCK}?     {ACCOUNTABLE return nodename; }


"&" 	{ACCOUNTABLE return terminal_and;}
"|" 	{ACCOUNTABLE return terminal_or;}
"!" 	{ACCOUNTABLE return terminal_not; }
"#" 	{ACCOUNTABLE return end_marker; }
"(" 	{ACCOUNTABLE return lpar; }
")" 	{ACCOUNTABLE return rpar; }
\/\/.*	{ACCOUNTABLE }

"==>" 	{ACCOUNTABLE return turnsto;}

<<EOF>>	{ACCOUNTABLE  return EOF;}                     // ?????????

" " 	{nchar++;}                                     // Spaces allowed for readability

\n|\r|\n\r|\r\n 	{nline++; nchar=0;}            // ?????????

.	{nchar++; yyerror ("Lexical error: Unexpected character");}

%%

int yywrap() {
	return(1);
}
