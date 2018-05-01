#ifndef CSP_INCLUDE_HH
#define CSP_INCLUDE_HH

#include "tag.hh"

namespace csp {

    /** @brief <csp:include>
     *
     * This class implements a CSP tag include.
     */
    class Include: public Tag {
    public:
	/**
	 * A constructor that instantiate a base class Tag.
	 * Tag::header is set FALSE.
	 *
	 * @param alias By this parameter it's possible to give a new tag
	 * name as alias.
	 */
	Include(const std::string &alias = "include"): Tag(alias, 0) {}

	/**
	 * This member function has to be invoked when
	 * the influence of the tag has begun. Checkes that
	 * all necessary attributes are given.
	 *
	 * @param attributes The attributes of the tag.
	 * @throw std::logic_error csp:include missing 'file' attribute.
	 */
	void open(const std::map<std::string, std::string> &attributes);

	/**
         * This is an overloaded member function, provided for convenience.
	 * Opening of the include tag with this function is an error
	 * because include doesn't take inline content.
	 *
	 * @param content The tag inline content.
	 * @throw std::logic_error csp:include doesn't take
	 * inline content.
	 */
	void open(const std::string &content);

	/**
	 * Finalizes the CGI scripting:
	 *  - Executes CSP compiler recursevely by using popen wrapper coded by
	 *  Alex Vinokur.
	 *  - Writes 'system(file.cgi)' to Tag::cgi.
	 *  .
	 *
	 * @throw std::logic_error Possible error messages from
	 * csp compiler.
	 */
	void close();

	/**
         * This is an overloaded member operator<<, provided for convenience.
	 * The include tag cannot have a content.
	 *
	 * @throw std::logic_error csp:include cannot have a
	 * content.
	 */
	Tag& operator<<(const std::string &content);
    };
}

#endif

