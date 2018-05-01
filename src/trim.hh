#ifndef TRIM_HH
#define TRIM_HH

//
// Trim away leading and trailing whitespaces
//
inline std::string trim(const std::string& str, const std::string& trim = " \t")
{
    size_t beg = str.find_first_not_of(trim);
    size_t end = str.find_last_not_of(trim);
    return (beg != std::string::npos) ? str.substr(beg, end - beg + 1) : ""; 
}

#endif
