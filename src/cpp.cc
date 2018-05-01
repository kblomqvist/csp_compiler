#include <string>
#include <map>
#include <stdexcept>
#include "cpp.hh"
#include "trim.hh"

using namespace std;

void csp::Cpp::open(const map<string, string>& /*a*/) {
    string err = "csp:" + name + " cannot have attributes.";
    throw logic_error(err);
}

void csp::Cpp::open(const string &c) {
    cgi << "// --8<-- START csp:cpp --8<--\n"
	<< c;
}

void csp::Cpp::close() {
    cgi << endl << "// -->8-- END csp:cpp -->8--";
}

Tag& csp::Cpp::operator<<(const string &c) {
    cgi << c;
    return *this;
}

