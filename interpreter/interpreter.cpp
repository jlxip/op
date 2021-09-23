#include "interpreter.hpp"

std::list<Scope> scopes;
size_t lineno = 0;

void interpreter(Block* main);
void startExecution(Block* main) {
	initBase();
	interpreter(main);
}

Value interpretUnary(UnaryStatement* st);
Value interpretBinary(BinaryStatement* st);
Value interpretIf(IfStatement* st);
void interpreter(Block* main) {
	scopes.push_front(Scope());

	for(auto const& x : *main) {
		++lineno;

		switch(x->type) {
		case Statement::UNARY:
			interpretUnary((UnaryStatement*)x);
			break;
		case Statement::BINARY:
			interpretBinary((BinaryStatement*)x);
			break;
		case Statement::IF:
			interpretIf((IfStatement*)x);
			break;
		default:
			std::cerr << "ERR: " << lineno << ": " <<
				"Unrecognized statement type." << std::endl;
			return;
		}
	}

	scopes.pop_front();
}

Value interpretUnary(UnaryStatement* st) {
	std::cout << "Unary" << std::endl;
	return Value();
}

Value interpretBinary(BinaryStatement* st) {
	// Does the operator start with '$' (var creation)
	std::cout << "Now parsing: ";
	std::cout << join(st->id1) << ' ' << st->oper << ' ' << join(st->id2) << std::endl;
	if(st->oper[0] == '$') {
		// Variable creation
		// Does id2 exist?
		Value& two = findValue(st->id2);
		
	} else {
		// Regular operators
		// Does id1+'.'+oper exist?
		auto withop = st->id1;
		withop.push_back(st->oper);
		Value& op = findValue(withop);
	}

	std::cout << "Nice!" << std::endl;
	return Value();
}

Value interpretIf(IfStatement* st) {
	return Value();
}
