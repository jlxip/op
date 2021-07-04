#include "op.hpp"
#include <iostream>

int main(int agrc, char* argv[]) {
	yyparse();
	return 0;
}

ChadID* v2cID(VirginID* id) {
	auto* ret = new ChadID;
	ret->reserve(id->size());
	for(auto const& x : *id)
		ret->push_back(x);
	delete id;
	return ret;
}

ChadBlock* v2cBlock(VirginBlock* block) {
	auto* ret = new ChadBlock;
	ret->reserve(block->size());
	for(auto const& x : *block)
		ret->push_back(x);
	delete block;
	return ret;
}

/*Value BinaryStatement::run() {

}*/

Value runBlock(ChadBlock* block) {
	for(size_t i=0; i<block->size()-1; ++i)
		(*block)[i]->run();
	return (*block)[block->size()-1]->run();
}

Value IfStatement::run() {
	if(runBlock(check))
		return runBlock(ifTrue);
	else if(hasElse)
		return runBlock(ifFalse);

	Value ret;
	ret.type = Value::UINT;
	ret.isArray = false;
	ret.val.u = 0;
	return ret;
}
