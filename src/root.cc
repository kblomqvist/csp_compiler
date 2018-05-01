#include <string>
#include <map>
#include <iterator>
#include <stdexcept>
#include "trim.hh"
#include "root.hh"

using namespace std;
 
void csp::Root::open(const map<string, string>& /*a*/) {}

void csp::Root::open(const string& /*s*/) {}

void csp::Root::close() {}

Tag& csp::Root::operator<<(const std::string &content)
{
    if(trim(content, " \t\n").empty())
	return *this;
    else
	return Tag::operator<<(content);
}
