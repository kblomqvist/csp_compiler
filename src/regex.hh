#ifndef REGEX_HH
#define REGEX_HH

#include <string>
#include <list>
#include <map>
#include <sys/types.h>
#include <regex.h>
#include <cstring>

namespace regex
{
    
    /** \brief Structure for storing substring start and end
     * positions of matched regular expression
     */
    struct Match
    {
	/**
	 * Construct a substring match structure 
	 * @param beg_ Start position of a substring match
	 * @param end_ End position of a substring match
	 */
	Match(regoff_t beg_, regoff_t end_) : beg(beg_), end(end_) {}
	regoff_t beg; /**< start position of a match, -1 if no match found */
	regoff_t end; /**< end position of a match, -1 if no match found */
    };
    
    /** \brief Class for wrapping regex_t and associated matches
     */
    class Pattern
    {
    public:
	/**
	 * Define regular expression and how many substring matches is expected 
	 * @param pattern Regular expression in extended syntax
	 * @param matchCount How many substring matches is expexted
	 */
	Pattern(const std::string& pattern, unsigned int matchCount = 0);
	~Pattern();
	/**
	 * Given string is matched against this regular expression
	 * @param str String to match against this regular expression
	 * @return regexec() error code. 0 = matching succeeded
	 */
	int match(const char* str);
	/**
	 * Request the start and end position of a match in a regular expression.
	 * @param index The index of substring for which the start and end
	 * positions are requested
	 * @return Returns Match structure of requested substring match
	 */
	const regmatch_t& operator()(unsigned int index) const;
    private:
	size_t      _matchCount;
	regmatch_t* _matches;
	regex_t     _rex;
    };
    
    /** \brief Class for parsing a string against regular expressions.
     * Keeps track of position where parsing proceeds.
     */
    class Parser
    {
    public:
	Parser();
	/**
	 * Set parser to parse given string. Resets the position of
	 * parsing to the beginning of the given string
	 * @param str String to parse against regular expressions
	 */
	Parser(char* str);
	Parser(const Parser& other);
	Parser& operator=(const Parser& other);
	/**
	 * Set the length of the string under parsing. This is useful when
	 * the string is actually a data buffer to which new data is appended
	 * and current parse position has to be maintained.
	 * @param length The changed length of the parsed string
	 */
	Parser& operator=(size_t length);
	/**
	 * Set parser to parse given string. Resets the position of
	 * parsing to the beginning of the given string
	 * @param str String to parse against regular expressions
	 */
	Parser& operator=(char* str);
	/**
	 * Request the start and end position of a match in a regular expression.
	 * Use after successful match() or matchNext() method call.
	 * @param index The index of substring for which the start and end
	 * positions are requested
	 * @return Returns Match structure of requested substring match
	 */
	const Match operator()(unsigned int index) const;
	/**
	 * Request the substring of a match in a regular expression. Use after successful
	 * match() or matchNext() method call.
	 * @param index The index of substring match requested
	 * @return Returns the requested substring match of matched regular expression
	 */
	std::string operator[](unsigned int index) const;
    public:
	/**
	 * Do matching against given regular expression
	 * @param rex The regular expression to match against
	 * @param pos Start matching from this position in the underlying buffer
	 * @return regexec() error code. 0 = matching succeeded
	 */
	int match(Pattern& rex, size_t pos = 0);
	/**
	 * Do matching against given regular expression by continuing from the current
	 * matching position of the parser.
	 * @param rex The regular expression to match against
	 * @return regexec() error code. 0 = matching succeeded
	 */
	int matchNext(Pattern& rex);
	/**
	 * The current parsing position in the parsed string / buffer
	 * @return Parsing position
	 */
	size_t matchDone() const;
	/**
	 * The length of data still to be parsed in the string / buffer
	 * @return Length of data to be parsed in current parse string / buffer
	 */
	size_t matchLeft() const;
    private:
	char*    _str;
	size_t   _length;
	size_t   _curPos;
	size_t   _nxtPos;
	Pattern* _rex;
    };
}

#endif
