#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "../op.hpp"
#include <iostream>

struct Scope {
	std::unordered_map<std::string, Value> vars;
	std::unordered_multimap<std::string, std::string> children;
};

// Most recent at front
extern std::list<Scope> scopes;
// Line of current statement
extern size_t lineno;

std::string join(const ID&);
inline void err() { std::cerr << "Error: " << lineno << ": "; }
void initBase();
Value& findValue(const ID&);

#endif
