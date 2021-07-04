#include "op.hpp"
#include <iostream>

int main(int agrc, char* argv[]) {
	std::cout << "Ayo" << std::endl;
	yyparse();
	return 0;
}

static void recPrint(ID* id) {
	if(id->isTerminal)
		std::cout << id->terminal << " (T) ";
	else {
		std::cout << " (F) ";
		recPrint(id->first);
		std::cout << " (S) ";
		recPrint(id->second);
	}
	if(id->isLiteral)
		std::cout << " (L) ";
}

void apply(ID* id1, char* op, ID* id2) {
	std::cout << "id1: "; recPrint(id1); std::cout << std::endl;
	std::cout << "op:  " << op << std::endl;
	std::cout << "id2: "; recPrint(id2); std::cout << std::endl;

	/*std::cout << "id1: " << id1.second->first;
	recPrint(id1.second);

	std::cout << "op:  " << op << std::endl;
	std::cout << "id2: " << id2.first << std::endl;*/
}
