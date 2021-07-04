#ifndef OP_HPP
#define OP_HPP

#include <string>

int yyparse();
void yyerror(const std::string&);

struct ID {
	char* terminal;
	ID *first, *second;
	bool isTerminal, isLiteral;

	ID() = default;

	ID(char* terminal, bool isLiteral)
		: terminal(terminal), isTerminal(true), isLiteral(isLiteral)
	{}

	ID(ID* first, ID* second)
		: first(first), second(second), isTerminal(false)
	{}
};

void apply(ID* id1, char* op, ID* id2);

#endif
