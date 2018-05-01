#ifndef PARSER_H
#define PARSER_H

#include <map>
#include "tag.hh"
#include "regex.hh"

namespace 
{
    //
    // 0 substring captures
    //
    std::string S1 = "[ \t\r\n]";
    std::string S0 = S1 + "*";
    std::string SN = S1 + "+";
    std::string Else = "${" + S0 + "else" + S0 + "}";
    //
    // 1 substring captures
    //
    std::string Name = "([[:alpha:]_:][[:alnum:]_:.-]*)";
    std::string Text = "(<*[^<]+)";
    //
    // 2 substring captures
    //
    std::string Close = "^</" + S0 + "csp" + S0 + ":" + S0 + Name + S0 + "(>)?";
    std::string Variable = "\\$\\{" + S0 + Name + S0 + "\\}";
    //
    // 3 substring captures
    //
    std::string Quoted = "(\"([^\"]*)\"|'([^']*)')";
    //
    // 4 substring captures
    //
    std::string Attribute = SN + Name + S0 + "=" + S0 + Quoted;
    //
    // 7 substring captures
    //
    std::string Open = "^<" + S0 + "csp" + S0 + ":" + S0 + Name + "((" + Attribute + ")*)" + S0 + "(/>|>)?";
}

/** \brief Parser to parse CSP source code
 */


class CSPParser
{
public:
    /**
     * Enumeration for token types found when parsing CSP code.
     */
    typedef enum 
    { 
	EOL = 1, /**< End Of Line - current line is fully parsed */ 
	OPEN,    /**< Tag Opening found */
	CLOSE,   /**< Tag Closing found */
	TEXT,    /**< Text chunk found */
	PARTIAL  /**< Partial tag found, need more input */
    } token;
public:
    CSPParser();
    ~CSPParser();
    /**
     * Set next line of CSP source to be parsed. 
     * @param line Line to be parsed.
     * @throw std::logic_error Syntax error in CSP source.
     */
    void setParseLine(const std::string& line);
    /**
     * Is the last parsed tag an inline version (<tag ... />)
     * @return boolean to indicate if the tag is an inline version
     */
    bool isTagInline();
    /**
     * Get the type of last parsed tag.
     * @return Name of the last parsed tag
     */
    std::string getTagType();
    /**
     * Get the object of last parsed CSP tag. Use after findNextToken() has returned OPEN.
     * @return Last parsed tag object.
     */
    Tag* getTag();
    /**
     * Get a parsed text chunk. Use after findNextToken() has returned TEXT.
     * @return Last parsed text chunk.
     */
    std::string getText();
    /**
     * Get the attributes of last parsed tag as a string. Use after findNextToken() has returned OPEN.
     * @return Attributes as std::string
     */
    std::string getAttributesAsString();
    /**
     * Get the attributes of last parsed tag as a map. Use after findNextToken() has returned OPEN.
     * @return Attributes as std::map.
     */
    std::map<std::string, std::string> getAttributesAsMap();
    /**
     * Find next token from CSP source line.
     * @return EOL - current line is fully parsed, OPEN - CSP tag opening was found,
     * CLOSE - CSP tag closing was found, TEXT - plain text was found, NONE - partial tag found,
     * need more input
     */
    CSPParser::token findNextToken();
    /**
     * Get next CSP variable tag from the source. Call after whole CSP source has been parsed.
     * @return true - if variable tag was found, false - no more variable tags found. 
     */
    bool findNextVariable();
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

    const regex::Match operator()(unsigned int index); 
    std::string operator[](unsigned int index); 
private:
    regex::Parser _cspParser;
    regex::Parser _attributeParser;
    regex::Pattern _openTag;
    regex::Pattern _closeTag;
    regex::Pattern _variableTag;
    regex::Pattern _tagAttribute;
    regex::Pattern _textChunk;
    std::string _line;
    std::string _text;
    Tag* _tag;
};

/** @example example2_parser.cc
 * This is an example of how to use the Parser class.
 */

#endif
