
#include "regex.hh"

regex::Pattern::Pattern(const std::string& pattern, unsigned int matchCount) : 
    _matchCount(matchCount + 1), 
    _matches(0)
{
    regcomp(&_rex, pattern.c_str(), REG_EXTENDED);
    _matches = new regmatch_t[_matchCount];
}

regex::Pattern::~Pattern()
{
    regfree(&_rex);
    delete[] _matches;
}

int regex::Pattern::match(const char* str)
{
    return regexec(&_rex, str, _matchCount, _matches, 0);
}

const regmatch_t& regex::Pattern::operator()(unsigned int index) const
{
    return _matches[index];
}

regex::Parser::Parser() : 
    _str(0), _length(0), _curPos(0), _nxtPos(0), _rex(0) 
{
}

regex::Parser::Parser(char* str) : 
    _str(str), _length(strlen(_str)), _curPos(0), _nxtPos(0), _rex(0) 
{
}

regex::Parser::Parser(const regex::Parser& other)
{
    _str = other._str;
    _length = other._length;
    _curPos = other._curPos;
    _nxtPos = other._nxtPos;
    _rex = other._rex;
}

regex::Parser& regex::Parser::operator=(const regex::Parser& other)
{
    if(this != &other)
    {
	_str = other._str;
	_length = other._length;
	_curPos = other._curPos;
	_nxtPos = other._nxtPos;
	_rex = other._rex;            
    }
    return *this;
}

regex::Parser& regex::Parser::operator=(size_t length)
{
    _length = length;
    return *this;
}

regex::Parser& regex::Parser::operator=(char* str)
{
    _str = str;
    _length = strlen(_str);
    _curPos = 0;
    _nxtPos = 0;
    return *this;
}

const regex::Match regex::Parser::operator()(unsigned int index) const
{
    size_t pos = (*_rex)(index).rm_so >= 0 ? _curPos : 0;
    return Match((*_rex)(index).rm_so + pos, (*_rex)(index).rm_eo + pos);
    
}

std::string regex::Parser::operator[](unsigned int index) const
{
    return std::string(_str, (*_rex)(index).rm_so + _curPos, (*_rex)(index).rm_eo - (*_rex)(index).rm_so);
}

int regex::Parser::match(regex::Pattern& rex, size_t pos)
{
    _nxtPos = pos;
    
    return matchNext(rex);
}

int regex::Parser::matchNext(regex::Pattern& rex)
{
    _curPos = _nxtPos;
    
    if(_curPos >= _length) return 1;
    
    _rex = &rex;
    
    int ret = _rex->match(&_str[_curPos]);
    
    if(!ret) _nxtPos += (*_rex)(0).rm_eo;
    
    return ret;
}

size_t regex::Parser::matchDone() const
{
    return _curPos;
}

size_t regex::Parser::matchLeft() const
{
    return _length - _curPos;
}
