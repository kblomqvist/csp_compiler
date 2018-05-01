#ifndef ESCAPESTRING_HH
#define ESCAPESTRING_HH

#include <string>

/**
 * @brief Real escapes quotation marks and backslashes.
 *
 * @param A constant reference to the string that is liked to be
 * escaped.
 * @return Escaped string.
 */
inline std::string escapeString(const std::string &str) {
    std::string es; // escaped string
    for(size_t i = 0; i < str.size(); ++i) {
	if(str[i] == '\"' || str[i] == '\'') {
	    es += "\\";
	    es += str[i];
	}
	else if(str[i] == '\\') {
	    if(str[i+1] == 'n' ||
		str[i+1] == 't' ||
		str[i+1] == 'r' ||
		str[i+1] == 'b' ||
		str[i+1] == 'f'
		)
		es += str[i];
	    else
		es += "\\\\";
	}
	else
	    es += str[i];
    }
    return es;
}

inline std::string unescapeNewline(const std::string &str) {
    std::string es; // unescaped string
    for(size_t i = 0; i < str.size(); ++i) {
	if(str[i] == '\n') {
	    es += "\\n";
	}
	else
	    es += str[i];
    }
    return es;
}

#endif

