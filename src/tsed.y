%{
	#include <iostream>
	#include <stdio.h>
	#include <string.h>
	#include <string>
	#include <sstream>
	#include "node_machine.h"

	using namespace std;

	int yylex(void);
	int yyerror(const char *);
	extern char * yytext;
	//	extern "C" int yyparse (void);
%}

%union {
   std::string * output;
   int tk;
};

%token
imdoms
doms
imdomted
domted
siblproper
imlsibl
imrsibl
lsibl
rsibl

fstchildpar
lastchildpar
fstchild
lastchild

onlychildpar
onlychild

lmanc
rmanc
lmdesc
rmdesc

nthparent
nthchild
nthparent_end
nthchild_end

imprec
imsucc
prec
succ

singdescpat
singascpath

EQ
HOMON

nimdoms
ndoms
nimdomted
ndomted
nsiblproper
nimlsibl
nimrsibl
nlsibl
nrsibl

nfstchildpar
nlastchildpar
nfstchild
nlastchild

nonlychildpar
nonlychild

nlmanc
nrmanc
nlmdesc
nrmdesc

nnthparent
nnthchild
nnthparent_end
nnthchild_end

nimprec
nimsucc
nprec
nsucc

nsingdescpat
nsingascpath

nEQ
nHOMON

%token nodename
end_marker
lpar
rpar
terminal_and
terminal_or
terminal_not

node_range_filler

turnsto

%type <output> search_expression
%type <output> search_primary
%type <output> opt_restrictions
%type <output> restrictions
%type <output> restrictions_and
%type <output> restrictions_not
%type <output> restriction
%type <output> search_second
%type <output> node_specifier

%%

start:
	search_expression //   turnsto   replacement_expression
		{cout<< *$1 <<endl;}
	;

search_expression:
	search_primary opt_restrictions
		{	stringstream ss;
			ss << "<search> "<< *$1 <<" <restrictions> "<< *$2 <<" </restrictions></search>";
			$$ = new string(ss.str()); }
	;


opt_restrictions:
	restrictions
		{ $$ = new string(*$1);}
	|
		{ $$ = new string();}
	;

restrictions:
	restrictions terminal_or restrictions_and
		{	stringstream ss;
			ss << *$1 << " or " << *$3;
			$$ = new string(ss.str());}
	| restrictions_and
		{ $$ = $1; }
	;

restrictions_and:
	restrictions_and terminal_and restrictions_not
		{	stringstream ss;
			ss << *$1 << " and " << *$3;
			$$ = new string(ss.str()); }
	|	restrictions_and restrictions_not		/* same as AND */
		{ stringstream ss;
			ss << *$1 << " hidden_and " << *$2;
			$$ = new string(ss.str()); }
	| restrictions_not
		{ $$ = $1;}
	;

restrictions_not:
	terminal_not restrictions_not
		{	stringstream ss;
			ss << "not " << *$2;
			$$ = new string(ss.str()); }
	|	lpar restrictions rpar
		{	stringstream ss;
				ss << "(" << *$2 << ")";
				$$ = new string(ss.str());}
	| restriction  /* break precedence, [] on tgrep*/
		{$$ = $1;}
	;

restriction:
	imdoms search_second
		{	stringstream ss;
			ss << "<im_dominates> " << *$2;
			$$ = new string(ss.str()); }
	|	doms search_second
		{	stringstream ss;
			ss << "<dominates> " << *$2;
			$$ = new string(ss.str()); }
	|	imdomted search_second
		{ stringstream ss;
			ss << "<im_dominated> " << *$2;
			$$ = new string(ss.str()); }
	| domted search_second
		{ stringstream ss;
			ss << "<dominated> " << *$2;
			$$ = new string(ss.str()); }
	;

search_second:
	lpar search_expression rpar
		{ stringstream ss;
			ss << "<sub> "<< *$2 << " </sub>";
			$$ = new string(ss.str()); }
	| search_primary
		{ $$ = $1;}
	;

search_primary:
	node_specifier
		{ $$ = $1;}
	;

node_specifier:
	nodename
		{ stringstream ss;
		  Machine machine = Machine(string(yytext));
			Nodespec node_spec = machine.execute();

			if(node_spec.type == NODE_EXCEPTION) yyerror(node_spec.errors.c_str());

			// ss << "<node_name="<< node_spec.regex.c_str() << ">";

			/* for more comprehensive debug */

			/*

			string type_of_nodespec_array[] = {"NODE_EXCEPTION","SIMPLE_NODE","RANGE_PLACEHOLDER","EMPTY_NODE"};
			string type_array[] = {"COPY_PLACEHOLDER_FULL","CUT_PLACEHOLDER_FULL","COPY_PLACEHOLDER_REF","CUT_PLACEHOLDER_REF","NONE"};

			ss << endl << "=======" << endl;
			ss << " node_name "<< string(yytext) << endl;
			ss << "  regex: " << node_spec.regex.c_str() << endl;
			ss << "  type_of_nodespec " << type_of_nodespec_array[node_spec.type_of_nodespec+1] << endl;
			ss << "  type " << type_array[node_spec.type] << endl;
			ss << "  holder_number " << node_spec.holder_number << endl;
			ss << "  parenthesis " << node_spec.parenthesis << endl;
			ss << "  holder_start " << node_spec.holder_start << endl;
			ss << "  errors " << node_spec.errors;
			ss << endl << "=======" << endl;

			*/


			$$ = new string(ss.str()); }
	| end_marker
		{ $$ = new string("<end_marker>"); }
	;

// replacement_expression: tree_seq;
// tree_seq: tree_seq tree  |  tree   ;
// tree: node |  // folha
//       lpar node tree_seq rpar ;      
// node: node |                        /* similar to nodename */
//       primary_placeholder_instance |
//       auxiliary_placeholder_instance |
// 	  ;


%%

#include "lex.yy.c"

int main(int argc, char *argv[]) {
   yy_scan_string (argv[1]);

   if (yyparse()==0); // cout << "ANÁLISE COMPLETADA COM SUCESSO" << endl;
   else cout << "OOPS!" << endl;
}

int  yyerror(const char * s) {
  fprintf(stderr, "ERROR: %s, in line %d, column %d, near token %s\n", 
	  s, nline, nchar, yytext);
  return 1;
}
