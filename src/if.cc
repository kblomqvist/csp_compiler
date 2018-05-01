#include <string>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include "if.hh"

using namespace std;

void csp::If::open(const map<string, string> &a) {
    // check that attributes are ok
    if (a.find("clause") != a.end())
	attributes = a; // save attributes
    else {
	string err = "csp:" + name + " missing 'clause' attribute.";
	throw logic_error(err);
    }

    // get left, operator and right from the given clause
    std::istringstream iss(attributes["clause"]);
    std::string l; // left
    std::string op; // operator
    std::string r; // right
    iss >> l >> op >> r;

    cgi << "// --8<-- START csp:if --8<--\n"
        << "if (" << l << " "
       	<< op << " "
	<< r << ") {\n";
}

// /*c*/ in order that compiler won't show warning
void csp::If::open(const string& /*c*/) {
    string err = "csp:" + name + " doesn't take inline content";
    throw logic_error(err);
}

void csp::If::close() {
    cgi	<< "}\n"
        << "// -->8-- END csp:if -->8--";
}

