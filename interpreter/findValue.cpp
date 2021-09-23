#include "interpreter.hpp"

Value& findValue(const ID& id) {
	// Look through the scopes
	for(auto& s : scopes) {
		// Try the whole id (for instance, a.c.x).
		// If it doesn't exist, try a.c
		// This is to show a coherent error
		auto it = s.vars.find(join(id));
		if(it != s.vars.end())
			return (*it).second;
	}

	// Not found. Boutta exit. Show a coherent error.
	for(auto const& s : scopes) {
		// If id is "a.c.x", try "a.c" and "a"
		auto itn = id.end(); --itn;
		for(; itn != id.begin(); --itn) {
			ID cutid(id.begin(), itn);
			// Exists?
			if(s.vars.find(join(cutid)) != s.vars.end()) {
				// Yes, problem is right above
				err(); std::cerr << "in \"" << join(cutid) <<
					"\", \"" << *itn << "\" does not exist." <<
					std::endl;
				exit(100);
			}
			// No. Problem might be below ("a" instead "a.c")
		}
	}

	// If reached this point, given id="a.c.x", then "a" doesn't exist.
	err(); std::cerr << "\"" << *id.begin() <<
		"\" doesn't exist." << std::endl;
	exit(100);
}
