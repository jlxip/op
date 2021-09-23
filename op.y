%{
#include "op.hpp"
#include <iostream>

int yylex();

static size_t lineno = 0;
%}

%union {
	char* _id;
	char* _op;
	char* _lit;
	ID* _obj;
	Statement* _statement;
	IfStatement* _if;
	Block* _block;
}

%start start

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
%type <_block> block line

%%

start: line { startExecution($1); }

line: statement line { $$=$2; $$->push_front($1); }
|     lbreak line { $$=$2; ++lineno; }
|     comment line { $$=$2; }
|     separator line { $$=$2; }
|     /* ɛ */ { $$=new Block; }
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
	aux->lineno = lineno;
	aux->id1=*$1; delete $1;
	aux->oper = $2;
	aux->id2=*$3; delete $3;
	$$=aux; }
|      Popen statement Pclose { $$=$2; }
;

obj: id { $$=new ID; $$->push_back($1); }
|    lit { $$=new ID; $$->push_back($1); }
|    obj dot id { $$=$1; $$->push_back($3); }
|    Popen obj Pclose { $$=$2; }
;

ifclause: block then block {
	$$=new IfStatement;
	$$->lineno = lineno;
	$$->check=$1;
	$$->ifTrue=$3; }
;
elseclause: notthen block {
	$$=new IfStatement;
	$$->lineno = lineno;
	$$->ifFalse=$2; }
;

block: Copen line Cclose { $$=$2; }
|      small {
	auto* aux = new Block;
	aux->push_back($1);
	$$=aux; }
;

%%

void yyerror(const std::string& s) { std::cerr << "Error: " << s << std::endl; }
