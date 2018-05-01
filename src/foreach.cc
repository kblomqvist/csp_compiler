#include <string>
#include <map>
#include <stdexcept>
#include "foreach.hh"

using namespace std;

void csp::ForEach::open(const map<string, string> &a) {
    // check that attributes are ok
    if (a.find("var") != a.end() && a.find("items") != a.end())
	attributes = a; // save attributes
    else {
	string err = "csp:" + name + " missing attributes.";
	throw logic_error(err);
    }

    // get type and object from var attribute
    std::istringstream iss(attributes["var"]);
    std::string t; // type
    std::string o; // object
    iss >> t >> o;

    cgi << "// --8<-- START csp:foreach --8<--\n"
	<< "for (size_t " << o << "_i = 0; "
        << o << "_i < "
	<< attributes["items"] << ".size(); "
        << o << "_i++) {\n";
    cgi << "const " << t << " " << o << " = "
	<< attributes["items"] << "[" << o << "_i];\n";
}

// /*s*/ in order that compiler won't show warning
void csp::ForEach::open(const string& /*s*/) {
    string err = "csp:" + name + " doesn't take inline content.";
    throw std::logic_error(err);
}

void csp::ForEach::close() {
    cgi << "}\n"
	<< "// -->8-- END csp:foreach -->8--";
}

