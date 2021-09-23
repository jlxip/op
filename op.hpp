#ifndef OP_HPP
#define OP_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <list>

int yyparse();
void yyerror(const std::string&);

// ID
typedef std::list<std::string> ID;

// Value
struct Value {
	Value* parent;
	void* val;
	//bool isArray;
};

// Statements
struct Statement {
	enum { UNARY, BINARY, IF };
	size_t type;
	size_t lineno = ~0;
};

struct UnaryStatement : Statement {
	ID id;
	std::string op;

	UnaryStatement() { type = UNARY; }
};

struct BinaryStatement : Statement {
	ID id1, id2;
	std::string oper;

	BinaryStatement() { type = BINARY; }
};

// Bunch of statements
typedef std::list<Statement*> Block;

struct IfStatement : Statement {
	Block* check;
	Block* ifTrue;
	Block* ifFalse;
	bool hasElse;

	IfStatement() { type = IF; }
};

void startExecution(Block* block);

#endif
