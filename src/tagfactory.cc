#include <string>
#include <stdexcept>
#include "tagfactory.hh"
#include "stdcsp.hh"

Tag* TagFactory::produce(const std::string &tag) {
    if (tag == "page")
        return new csp::Page();

    else if (tag == "include")
	return new csp::Include();

    else if (tag == "cpp")
        return new csp::Cpp();

    else if (tag == "print")
        return new csp::Print();

    else if (tag == "foreach")
        return new csp::ForEach();

    else if (tag == "if")
	return new csp::If();

    else if (tag == "else")
	return new csp::Else();

    // Aliases
    else if (tag == "p") // print
	return new csp::Print("p");

    else if (tag == "i") // include
	return new csp::Include("i");

    // CSP Compiler helper tags
    else if (tag == "root") // DO NOT REMOVE!
	return new csp::Root();

    // Is not CSP tag
    else
        throw std::invalid_argument("Unknown type of tag");
}

