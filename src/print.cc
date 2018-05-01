#include <string>
#include <map>
#include <stdexcept>
#include "print.hh"

using namespace std;

void csp::Print::open(const string &c) {
    cgi << "// --8<-- START csp:print --8<--\n"
	<< "{\n"
	<< "std::string tmp = " << c << ";\n";
}

// /*a*/ in order that compiler won't show warning
void csp::Print::open(const map<string, string>& /*a*/) {
    string err = "csp:" + name + " cannot have attributes.";
    throw logic_error(err);
}

void csp::Print::close() {
    cgi	<< "std::cout << tmp;\n"
	<< "}\n"
	<< "// -->8-- END csp:print -->8--";
}

Tag& csp::Print::operator<<(const std::string &c) {
    cgi << "tmp = tmp + " << c << ";" << endl;
    return *this;
}

