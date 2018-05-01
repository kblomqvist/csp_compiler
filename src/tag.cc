#include <string>
#include <map>
#include <sstream>
#include <stdexcept>
#include "tag.hh"
#include "escapestring.hh"

using namespace std;

Tag::Tag(const string &_name, const bool _isHeader):
	name(_name), header(_isHeader) {}

Tag::~Tag() {}

void Tag::open(const map<string, string> &a) {
    attributes = a;
}

void Tag::open(const string &c) {
    *this << c;
}

bool Tag::isHeader() const {
    return header;
}

std::string Tag::getTagName() const {
    return name;
}

Tag& Tag::operator<<(const string &content) {
    cgi << "std::cout << \"" << unescapeNewline(escapeString(content)) << "\";" << endl;
    return *this;
}

Tag& Tag::operator<<(const Tag &t) {
    // t is nested tag for this
    cgi << t.cgi.str() << endl;
    return *this;
}

std::ostream& operator<<(std::ostream &out, const Tag &t) {
    out << t.cgi.str();
    return out;
}

