#include "op.hpp"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	if(argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
		return 1;
	}

	int file = open(argv[1], O_RDONLY);
	if(file < 0) {
		std::cerr << "Could not open: " << argv[1] << std::endl;
		return 2;
	}

	dup2(file, STDIN_FILENO);
	yyparse();
	return 0;
}
