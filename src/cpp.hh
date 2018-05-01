#ifndef CSP_CPP_HH
#define CSP_CPP_HH

#include <string>
#include <map>
#include "tag.hh"

namespace csp {

    /** @brief <csp:cpp>
     *
     * This class implements a CSP tag cpp.
     */

    class Cpp: public Tag {
    public:
	/**
	 * A constructor that instatiates a base class Tag.
	 * Tag::header is set to FALSE.
	 *
	 * @param alias By this parameter it's possible to give a new tag
	 * name as alias.
	 */
	Cpp(const std::string &alias = "cpp"): Tag(alias, 0) {}

	/**
	 * This is an overloaded member function, provided for convenience.
	 * The opening of the cpp tag with this function ignores
	 * the given attributes.
	 *
	 * @param attributes The attributes of the tag.
	 */
	void open(const std::map<std::string, std::string> &attributes);

	/**
	 * The opening of the cpp tag with this function writes
	 * the tag inline content as it is to Tag::cgi.
	 *
	 * @param content The tag inline content.
	 */
	void open(const std::string &content);

	/** 
	 * Finalizes the CGI scripting:
	 *  - Writes the content of the tag as it is to Tag::cgi.
	 *  .
	 */
	void close();

	/**
         * This is an overloaded member operator<<. The cpp
	 * tag doesn't 'cout' the given content.
	 */
	Tag& operator<<(const std::string &content);
    };
}

#endif

