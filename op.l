%{

#include <string>
#include "op.hpp"
#include <iostream>
#include "y.tab.h"

void yyerror(const std::string& s);
int yylex();
%}

%%

"\n" { return lbreak; }
"//".* { return comment; }
";" { return separator; }
"=>" { return then; }
"(" { return Popen; }
")" { return Pclose; }
"{" { return Copen; }
"}" { return Cclose; }
"." { return dot; }
[a-zA-Z_][a-zA-Z_0-9]* { yylval._id = strdup(yytext); return id; }
[^a-zA-Z_0-9.(){} \t\n]+ { yylval._op = strdup(yytext); return op; }
[0-9]+ { yylval._lit = strdup(yytext); return lit; }
[ \t] {}
. { std::cerr << "Unrecognized character: " << yytext << std::endl; exit(1); }

%%

int yywrap(void) { return 1; }
