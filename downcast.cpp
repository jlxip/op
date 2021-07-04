#include "op.hpp"

// Downcast from Value to bool
bool Value::downcast() const {
	if(isArray)
		return arr.size();

	switch(type) {
	case CHAR:
		return val.c;
	case INT:
		return val.i;
	case UINT:
		return val.u;
	case FLOAT:
		return val.f;
	}

	return false;
}
