%{
#include "op.hpp"
#include <iostream>

int yylex();
%}

%union {
	char* _id;
	char* _op;
	char* _lit;
	ID* _obj;
}

%start line

%token lbreak
%token comment
%token separator
%token then
%token Popen
%token Pclose
%token Copen
%token Cclose
%token dot
%token <_id> id
%token <_op> op
%token <_lit> lit

%type <_obj> obj

%%

line: statement line
|     lbreak line
|     comment line
|     separator line
|     /* ɛ */
;

statement: obj op obj { std::cout << "Statement!" << std::endl; apply($1, $2, $3); }
/*|          ifclause {}*/
|          Popen statement Pclose { ; }
;

obj: id { $$=new ID($1, false); }
|    lit { $$=new ID($1, true); }
|    obj dot id { $$=new ID($1, new ID($3, false)); }
|    Popen obj Pclose { ; }
;

/*ifclause: statement then statement { }
|         statement then block { }
;*/

/*block: '{' line '}' { ; }
  ;*/

%%

void yyerror(const std::string& s) { std::cerr << "Error: " << s << std::endl; }
