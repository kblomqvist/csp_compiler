#ifndef CSP_ELSE_HH
#define CSP_ELSE_HH

#include "tag.hh"

namespace csp {

    /** @brief <csp:else>
     *
     * This class implements a CSP tag else.
     */
    class Else: public Tag {
    public:
	/**
	 * A constructor that instantiates a base class Tag.
	 * Tag::header is set to FALSE.
	 *
	 * @param alias By this parameter it's possible to give a new tag
	 * name as alias.
	 */
	Else(const std::string &alias = "else"): Tag(alias, 0) {}

	/**
	 * This is an overloaded member function, provided for convenience.
	 * The opening of the else tag with this function ignores
	 * the given tag inline content.
	 *
	 * - Writes the C++ 'else' statement.
	 *
	 * @param content The tag inline content.
	 */
	void open(const std::string &content);

	/**
	 * This is an overloaded member function, provided for convenience.
	 * The opening of the else tag with this function ignores
	 * the given attributes.
	 *
	 * - Writes the C++ 'else' statement.
	 *
	 * @param attributes The tag attributes.
	 */
	void open(const std::map<std::string, std::string> &attributes);

	/**
	 * Finalizes the CGI scripting:
	 * - Closes the C++ 'else' statement.
	 */
	void close();
    };
}

#endif

