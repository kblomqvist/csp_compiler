#ifndef CSP_IF_HH
#define CSP_IF_HH

#include "tag.hh"

namespace csp {

    /** @brief <csp:if>
     *
     * This class implements a CSP tag if.
     */
    class If: public Tag {
    public:
	/**
	 * A constructor that instantiates a base class Tag.
	 * Tag::header is set to FALSE.
	 *
	 * @param alias By this parameter it's possible to give a new tag
	 * name as alias.
	 */
	If(const std::string &alias = "if"): Tag(alias, 0) {}

	/**
	 *  - Checks that all necessary attributes are given.
	 *  - Writes the header of C++ 'if' statement.
	 *  .
	 *
	 * @param attributes The attributes of the tag.
	 * @throw std::logic_error csp:if missing 'clause'
	 * attribute.
	 */
	void open(const std::map<std::string, std::string> &attributes);

	/**
         * This is an overloaded member function, provided for convenience.
	 * The opening of the if tag with this function is an error because
	 * if doesn't take inline content.
	 *
	 * @param content The tag inline content.
	 * @throw std::logic_error csp:if doesn't take inline
	 * content.
	 */
	void open(const std::string &content);

	/**
	 * Finalizes the CGI scripting:
	 *  - Writes the ending for the C++ 'if' statement.
	 *  .
	 */
	void close();
    };
}

#endif

