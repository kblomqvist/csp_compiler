#ifndef CSP_PAGE_HH
#define CSP_PAGE_HH

#include "tag.hh"

namespace csp {

    /** @brief <csp:page>.
     *
     * This class implements a CSP tag page.
     */
    class Page: public Tag {
    public:
	/**
	 * A constructor that instatiates a base class Tag.
	 * Tag::header is set to TRUE.
	 *
	 * @param alias By this parameter it's possible to give a new tag
	 * name as alias.
	 */
	Page(const std::string &alias = "page"): Tag(alias, 1) {}

    	/**
	 * This is an overloaded member function, provided for convenience.
	 * Opening of the page tag with this function is an
	 * error because page doesn't take inline content.
	 *
	 * @param content Tag inline content.
	 * @throw std::logic_error csp:page doesn't take inline content.
	 */
	void open(const std::string &content);

	/** 
	 * Finalizes the CGI scripting:
	 *  - Writes define and include C++ statements
	 *  according to given attributes.
	 *  .
	 */
	void close();

	/**
         * This is an overloaded member operator<<, provided for convenience.
	 * The page tag cannot have a content.
	 *
	 * @throw std::logic_error csp:page cannot have a content.
	 */
	Tag& operator<<(const std::string &content);
    };
}

#endif

