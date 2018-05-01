
#include <stdexcept>
#include "tagfactory.hh"
#include "trim.hh"
#include "parser.hh"

CSPParser::CSPParser() : 
    _openTag(Open, 8), 
    _closeTag(Close, 2),
    _variableTag(Variable, 1),
    _tagAttribute(Attribute, 4),
    _textChunk(Text, 1), _tag(0)
{	
}

CSPParser::~CSPParser()
{
}

void CSPParser::setParseLine(const std::string& line)
{
    // Set parser to parse the given line
    _line = line;
    _cspParser = const_cast<char*>(_line.c_str());
}

bool CSPParser::isTagInline()
{
    return _cspParser[8] == "/>";
}

std::string CSPParser::getTagType()
{
    return _cspParser[1];
}

Tag* CSPParser::getTag()
{
    return _tag;
}

std::string CSPParser::getText()
{
    return _text;
}

std::string CSPParser::getAttributesAsString()
{
    return _text = trim(_cspParser[2]);
}

std::map<std::string, std::string> CSPParser::getAttributesAsMap()
{
    std::map<std::string, std::string> attributeMap;
    
    //
    // Let's chop down the attributes
    //
    std::string attributes = _cspParser[2];
    
    _attributeParser = const_cast<char*>(attributes.c_str());
    
    while(!_attributeParser.matchNext(_tagAttribute))
    {
	if(_attributeParser(3).beg >= 0)
	{
	    attributeMap.insert(std::make_pair(trim(_attributeParser[1]), trim(_attributeParser[3])));
	}
	else
	{
	    attributeMap.insert(std::make_pair(trim(_attributeParser[1]), trim(_attributeParser[4])));
	}				
    }
    return attributeMap;
}

CSPParser::token CSPParser::findNextToken()
{
    if(!_cspParser.matchNext(_openTag))
    {
	// Did we match also the closing brace?
	
	if(_cspParser(8).beg < 0)
	{
	    return PARTIAL;
	}
	else
	{
	    std::string tagType = _cspParser[1];
	    
	    try
	    {
		_tag = TagFactory::produce(tagType);
		return OPEN;
	    }
	    catch(std::invalid_argument& e)
	    {
		//
		// Not a CSP tag, treat as plain text.
		//
		_text = _cspParser[0];
		return TEXT;
	    }
	}
    }
    else if(!_cspParser.matchNext(_closeTag))
    {
	//
	// Did we match also the closing brace?
	//
	if(_cspParser(2).beg < 0)
	{
	    return PARTIAL;
	}
	else
	{
	    return CLOSE;
	}
    }
    else if(!_cspParser.matchNext(_textChunk))
    {
	_text = _cspParser[0];
	return TEXT;
    }
    else
    {
	//
	// We must have partial tag left to parse... Let caller set new line to parse
	// with the remainings of this line in front of it
	//
	if(!_cspParser.matchLeft())
	{
	    return EOL;
	}
	else
	{	    
	    return PARTIAL;
	}
    }
}

bool CSPParser::findNextVariable()
{
    return !_cspParser.matchNext(_variableTag);
}

size_t CSPParser::matchDone() const
{
    return _cspParser.matchDone();
}

size_t CSPParser::matchLeft() const
{
    return _cspParser.matchLeft();
}

const regex::Match CSPParser::operator()(unsigned int index)
{
    return _cspParser(index);
} 

std::string  CSPParser::operator[](unsigned int index)
{
    return _cspParser[index];
} 
