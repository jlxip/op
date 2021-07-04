%{
#include "op.hpp"
#include <iostream>

int yylex();
%}

%union {
	char* _id;
	char* _op;
	char* _lit;
	VirginID* _obj;
	Statement* _statement;
	IfStatement* _if;
	VirginBlock* _vblock;
	ChadBlock* _block;
}

%start line

%token lbreak
%token comment
%token separator
%token then
%token notthen
%token Popen
%token Pclose
%token Copen
%token Cclose
%token dot
%token <_id> id
%token <_op> op
%token <_lit> lit

%type <_obj> obj
%type <_statement> statement small
%type <_if> ifclause elseclause
%type <_vblock> line
%type <_block> block

%%

line: statement line { $$=$2; $$->push_front($1); }
|     lbreak line { $$=$2; }
|     comment line { $$=$2; }
|     separator line { $$=$2; }
|     /* ɛ */ { $$=new VirginBlock; }
;

statement: ifclause {
	auto* aux = $1;
	aux->hasElse = false;
	$$=aux; }
|          ifclause elseclause {
	auto* aux = $1;
	aux->ifFalse = $2->ifFalse;
	aux->hasElse = true;
	delete $2;
	$$=aux; }
|          small { $$=$1; }
;

small: /*obj op { $$=makeUnary($1, $2); }*/
obj op obj {
	auto* aux = new BinaryStatement;
	auto* tmp=v2cID($1); aux->id1=*tmp; delete tmp;
	aux->oper = $2;
	tmp = v2cID($3); aux->id2=*tmp; delete tmp;
	$$=aux; }
|      Popen statement Pclose { $$=$2; }
;

obj: id { $$=new VirginID; $$->push_back($1); }
|    lit { $$=new VirginID; $$->push_back($1); }
|    obj dot id { $$=$1; $$->push_back($3); }
|    Popen obj Pclose { $$=$2; }
;

ifclause: block then block {
	$$=new IfStatement;
	$$->check=$1;
	$$->ifTrue=$3; }
;
elseclause: notthen block {
	$$=new IfStatement;
	$$->ifFalse=$2; }
;

block: Copen line Cclose { $$=v2cBlock($2); }
|      small {
	auto* aux = new VirginBlock;
	aux->push_back($1);
	$$=v2cBlock(aux); }
;

%%

void yyerror(const std::string& s) { std::cerr << "Error: " << s << std::endl; }
