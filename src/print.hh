#ifndef CSP_PRINT_HH
#define CSP_PRINT_HH

#include "tag.hh"

namespace csp {

    /** @brief <csp:print>
     *
     * This class implements a CSP print.
     */

    class Print: public Tag {
    public:
	/**
	 * A constructor that instatiates a base class Tag.
	 * Tag::header is set to FALSE.
	 * 
	 * @param alias By this parameter it's possible to give a new tag
	 * name as alias. By default 'print'.
	 */
	Print(const std::string &alias = "print"): Tag(alias, 0) {}

	/**
	 *  - Converts the inline content of the tag to the string.
	 *  .
	 *
	 * @param content The tag inline content.
	 */
	void open(const std::string &content);

	/**
	 * This is an overloaded member function, provided for convenience.
	 * Opening of the print tag with this function is an
	 * error because print cannot have attributes.
	 *
	 * @param attributes The attributes of the tag.
	 * @throw std::logic_error csp:print cannot have attributes.
	 */
        void open(const std::map<std::string, std::string> &attributes);

	/** 
	 * Finalizes the CGI scripting:
	 * - 'couts' the string.
	 */
	void close();

	/**
         * This is an overloaded member operator<<.
	 * - Converts the given content to the string.
	 * .
	 */
	Tag& operator<<(const std::string &content);
    };
}

#endif

