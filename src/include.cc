#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include "POPEN1.hh"
#include "include.hh"

using namespace std;

void csp::Include::open(const map<string, string> &a) {
    // check that attributes are ok
    if (a.find("file") != a.end())
	attributes = a; // save attributes
    else {
	string err = "csp:" + name + " missing 'file' attribute.";
	throw logic_error(err);
    }
}

// /*c*/ in order that compiler won't show warning
void csp::Include::open(const string& /*c*/) {
    string err = "csp::" + name + " doesn't take inline content.";
    throw logic_error(err);
}

void csp::Include::close() {
    // init command and result parameters to execute CSP compiler
    string csp_cmd = "./csp " + attributes["file"] + " -o " + attributes["file"] + ".csp -r";
    vector<string> csp_result;

    // execute CSP Compiler
    // check that CSP Compiler was executed successfully
    if (!popen_cplusplus(csp_cmd, csp_result)) {
	string err = "csp::" + name + " cannot execute popen_cplusplus.\n\t"
	    + "Hint: possible error in the value of file attribute.";
	throw logic_error(err);
    }

    // in case of CSP Compiler throws an error
    if (csp_result.size()) {
	string err = "CSP Compiler threw an error:\n";
	for(size_t i = 0; i < csp_result.size(); i++)
	    err += csp_result[i] + "\n";
	csp_result.clear();
	throw logic_error(err);
    }

    // CSP Compiler managed to compile included file to CGI
    // program
    else
	cgi << "// --8<-- START csp:include --8<--\n"
	    << "system(\"./" + attributes["file"] + ".csp\");\n"
	    << "// -->8-- END csp:include -->8--";
}

// /*c*/ in order that compiler won't show warning
Tag& csp::Include::operator<<(const std::string& /*c*/) {
    string err = "csp:" + name + " cannot have a content.";
    throw logic_error(err);
}

