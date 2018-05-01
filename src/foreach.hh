#ifndef CSP_FOREACH_HH
#define CSP_FOREACH_HH

#include "tag.hh"

namespace csp {

    /** @brief <csp:foreach>
     *
     * This class implements a CSP tag named foreach.
     */
    class ForEach: public Tag {
	public:
	    /**
	     * A constructor. Instantiates a base class Tag.
	     * Tag::header is set to FALSE.
	     *
	     * @param alias By this parameter it's possible to give a new tag
	     * name as alias.
	     */
	    ForEach(const std::string &alias = "foreach"): Tag(alias, 0) {}

	    /**
	     *  - Checks that all necessary attributes are given.
	     *  - Writes a header for C++ 'for' loop.
	     *  .
	     * @param attributes The attributes of the tag.
	     */
	    void open(const std::map<std::string, std::string> &attributes);

	    /**
	     * This is an overloaded member function, provided for convenience.
	     * Opening of the foreach tag with this function is an error
	     * because foreach doesn't take inline content.
	     *
	     * @param content The tag inline content.
	     * @throw std::logic_error csp:foreach doesn't take
	     * inline content.
	     */
	    void open(const std::string &content);

	    /** 
	     * Finalizes the CGI scripting:
	     *	- Closes the C++ 'for' loop.
	     *	.
	     */
	    void close();
    };
}

#endif

