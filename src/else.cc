#include <string>
#include <map>
#include "else.hh"

using namespace std;

void csp::Else::open(const map<string, string>& /*a*/) {
    // ignore attributes
    cgi.str("");
    cgi << "// --8<-- START csp:else --8<--" << endl
        << "else {" << endl;
}

void csp::Else::open(const string& /*c*/) {
    // ignore inlinen content
    cgi.str("");
    cgi << "// --8<-- START csp:else --8<--" << endl
        << "else {" << endl;
}

void csp::Else::close() {
    cgi	<< "}" << endl
        << "// -->8-- END csp:else -->8--";
}

