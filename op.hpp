#ifndef OP_HPP
#define OP_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <list>

int yyparse();
void yyerror(const std::string&);

// ID
typedef std::list<std::string> VirginID;
typedef std::vector<std::string> ChadID;

// Value
struct Value {
	enum { CHAR, INT, UINT, FLOAT };
	size_t type;
	bool isArray;
	union {
		char c;
		int64_t i;
		uint64_t u;
		long double f;
	} val;

	std::vector<Value> arr;

	inline operator bool() const { return downcast(); }
	bool downcast() const;
};

// Downcast to bool

// Scope (universe)
struct Scope {
	std::unordered_map<std::string, Value> vars;
};

// Statements
struct Statement {
	virtual Value run() = 0;
};

struct UnaryStatement : Statement {
	ChadID id;
	// Pretty sure this can be done faster
	std::string op;

	Value run() override;
};

struct BinaryStatement : Statement {
	ChadID id1, id2;
	std::string oper;

	Value run() override;
};

// Bunch of statements
typedef std::list<Statement*> VirginBlock;
typedef std::vector<Statement*> ChadBlock;

struct IfStatement : Statement {
	ChadBlock* check;
	ChadBlock* ifTrue;
	ChadBlock* ifFalse;
	bool hasElse;

	Value run() override;
};

// Functions to call from yacc
ChadID* v2cID(VirginID* id);
ChadBlock* v2cBlock(VirginBlock* id);

#endif
