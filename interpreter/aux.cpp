#include "interpreter.hpp"

// Some auxiliar functions

std::string join(const ID& id) {
	std::string ret = "";
	auto it = id.begin();
	for(size_t i=0; i<id.size()-1; ++i) {
		ret += *(it++);
		ret += '.';
	}
	ret += *it;
	return ret;
}
