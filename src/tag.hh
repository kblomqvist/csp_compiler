#ifndef CSP_TAG_HH
#define CSP_TAG_HH

#include <string>
#include <map>
#include <sstream>

/** @brief A base class for CSP tags.
 *
 * All CSP tags are derived from this class. This class
 * implements Tag::open() and Tag::close() member functions for
 * tag opening and closing and containers where to store tag attributes and
 * implemented CGI scripting.
 */

class Tag {
public:
    /**
     * A constructor.
     *
     * Initializes a tag by setting up a Tag::name and
     * the value for boolean Tag::isHeader. Tag::isHeader can be
     * used to check if the CGI scripting that tag implements
     * has to be written before main() function.
     * 
     * @param name Tag name.
     * @param isHeader TRUE if Tag::cgi has to be written before
     * main() function.
     */
    explicit Tag(const std::string &name, const bool isHeader);

    /**
     * A destructor.
     */
    virtual ~Tag();

    /**
     * This virtual member function is used to open typical tags
     * that have attributes and content. By default stores a given
     * attribute map to the invoked Tag.
     *
     * @param attributes The attributes of the tag.
     */
    virtual void open(const std::map<std::string, std::string> &attributes);

    /**
     * This virtual member function is used to open tags that are
     * typically inline type and don't have content. By default
     * converts a given string as a content of the tag.
     *
     * @param content The inline content of the tag.
     */
    virtual void open(const std::string &content);

    /**
     * This pure virtual member function has to be invoked when
     * the influence of the tag ends.
     */
    virtual void close() = 0;

    /**
     * This member function returns the value of Tag::header.
     *
     * @return Boolean
     */
    bool isHeader() const;

    /**
     * This member function gives the name of the tag.
     *
     * @return Tag::name.
     */
    std::string getTagName() const;

    /**
     * This virtual member operator<< takes a string as a content
     * of the tag. By default converts the given string straight
     * to the CGI scripting by 'couting' it. Given string is
     * escaped by using escapeString().
     *
     * @param content Tag content.
     * @return Tag A reference to this.
     */
    virtual Tag& operator<<(const std::string &content);

    /**
     * Appends the CGI scripting of the streamed Tag into this
     * Tag. Should be used to give tags that are nested for this.
     *
     * @param t A constant reference to other Tag
     * @return Tag A constant reference to this Tag.
     */
    Tag& operator<<(const Tag &t);

    /**
     * The valid CGI script of the tag is written out by this
     * streaming operator to another stream like standard
     * output.
     *
     * @param out A reference to the standard output stream.
     * @param t A constant reference to this.
     * @return std::ostream A reference to the standard output stream.
     */
    friend std::ostream& operator<<(std::ostream &out, const Tag &t);

public:
    /**
     * Tag name.
     */
    const std::string name;

    /**
     * TRUE == tag type is header, FALSE == tag type is main.
     */
    const bool header;

protected:
    /**
     * Map container for tag attributes.
     */
    std::map<std::string, std::string> attributes;

    /**
     * Stringstream where to write the valid CGI scripting
     * that tag implements.
     */
    std::ostringstream cgi;
};

/**
 * @example example_tag.cc
 * @example example2_tag.cc
 * This is an example of how to use the Tag class.
 */
#endif

