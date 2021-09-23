#include "interpreter.hpp"

// Base classes and their operators

Value *OBJ, *CHAR, *INT, *UINT, *FLOAT;
Value *IN, *OUT;

void initBase() {
	OBJ = new Value; CHAR = new Value; INT = new Value; UINT = new Value;
	FLOAT = new Value; IN = new Value; OUT = new Value;

	OBJ->parent = nullptr;
	CHAR->parent = INT->parent = UINT->parent = FLOAT->parent = OBJ;
	IN->parent = OUT->parent = OBJ;

	CHAR->val = new char(0);
	INT->val = new long long(0);
	UINT->val = new unsigned long long(0);
	FLOAT->val = new long double(0);
	IN->val = OUT->val = nullptr;
}
