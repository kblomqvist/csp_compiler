#ifndef CSP_ROOT_HH
#define CSP_ROOT_HH

#include "tag.hh"

namespace csp {

    /** @brief dummy CSP tag root
     *
     * This class implements a dummy CSP tag named 'root'. csp:root takes no
     * attributes map and produces of no code itself. It is used as a root
     * object in CSP parsing stack and is explicitly instantiated as the first
     * tag of a CSP program.
     *
     */
    class Root: public Tag {
	public:
	    /**
	     * A constructor. Instantiates a base class Tag.
	     */
	    Root(): Tag("root", 0) {}

	    /**
	     * This member function has to be invoked when
	     * the influence of the tag has begun. Function makes the
	     * following preliminary preparation to CGI scripting:
	     *
	     *  - Dummy. Does not store any values to the tag nor
	     *  write any output
	     *  .
	     * @param attributes Dummy attributes of root tag.
	     */
	    void open(const std::map<std::string, std::string> &attributes);

	    /**
	     * This is an overloaded member function, provided for convenience.
	     * Still, no output nor storing of attributes
	     *
	     * @param line Dummy content of the tag line. Not prosessed
	     * @throw std::logic_error csp::Root doesn't take
	     * inline content.
	     */
	    void open(const std::string &line);

	    /** 
	     * This member function has to be invoked when
	     * the influence of the tag ends.
	     *
	     * Finalizes the CGI scripting:
	     *	- Outputs all nested tags & content
	     *	.
	     */
	    void close();

	virtual Tag& operator<<(const std::string &content);

    };
}

/** @example example_root.cspf
 * This is an example of how to use csp:root in HTML.
 */

#endif

