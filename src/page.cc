#include <string>
#include <map>
#include <stdexcept>
#include "page.hh"

using namespace std;

void csp::Page::open(const string& /*c*/) {
    string err = "csp:" + name + " doesn't take inline content.";
    throw logic_error(err);
}

void csp::Page::close() {
    /* find will return an iterator to the matching element
     * if it is found or to the end of the map if the key is
     * not found.
     */
    if (attributes.find("contentType") != attributes.end())
        cgi << "#define _contentType \"" << attributes["contentType"] << "\"" << endl;

    if (attributes.find("language") != attributes.end())
        cgi << "#define _language \"" << attributes["language"] << "\"" << endl;

    if (attributes.find("errorPage") != attributes.end())
        cgi << "#define _errorPage \"" << attributes["errorPage"] << "\"" << endl;

    if (attributes.find("import") != attributes.end()) {
	if (attributes["import"][0] == '<')
	    cgi << "#include " << attributes["import"] << endl;
	else
	    cgi << "#include \"" << attributes["import"] << "\"" << endl;
    }
}

// /*c*/ in order that compiler won't show warning
Tag& csp::Page::operator<<(const std::string& /*c*/) {
    string err = "csp:" + name + " cannot have a content.";
    throw logic_error(err);
}

