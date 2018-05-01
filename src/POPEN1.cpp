// =======================================
// C++Wrapper around popen
// -----------------------
//   Alex Vinokur
//     mailto:alexvn@go.to
//     http://go.to/alexvn
// -----------------------
//   2002-10-22
// =======================================


// ==============================================
// Windows 2000 Professional
// MinGW 2.0.0.-2
// gcc/g++ version 3.2 (mingw special 20020817-1)
// ==============================================


// ================
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

#include <iostream>
#include <string>
#include <vector>

#include "POPEN1.hh"

using namespace std;

// =====================================
#define FATAL_MSG(msg) \
        cout << msg \
             << " : " \
             << (strerror (errno)) \
             << " [ " \
             << __FILE__ \
             << ", #" \
             << __LINE__ \
             << " ]" \
             << endl

#define ERROR_MSG(msg) \
        cout << msg \
             << " : " \
             << " [ " \
             << __FILE__ \
             << ", #" \
             << __LINE__ \
             << " ]" \
             << endl


// =====================================
bool popen_cplusplus (
		      const string&   command_i,
		      vector<string>& result_o
		      )
{
    bool            ret_boolValue = true;
    FILE*           fp;
    const int       SIZEBUF = 1234;
    char            buf [SIZEBUF];
    
    // ================================
    result_o = vector<string> ();
    // ================================
    
    if ((fp = popen(command_i.c_str (), "r")) == NULL)
    {
	FATAL_MSG ("Files or processes cannot be created");
	ret_boolValue = false;
	return ret_boolValue;
    }
    
    // ================================
    string  cur_string;
    while (fgets(buf, sizeof (buf), fp))
    {
	cur_string = buf;
	if (cur_string [cur_string.size () - 1] != '\n')
	{
	    ERROR_MSG ("SIZEBUF too small (" << SIZEBUF << ")");
	    ret_boolValue = false;
	    return ret_boolValue;
	}
	assert (cur_string [cur_string.size () - 1] == '\n');
	result_o.push_back (cur_string.substr (0, cur_string.size () - 1));
    }
    
    // ================================
    if (pclose(fp) == -1)
    {
	FATAL_MSG ("Cannot execute pclose");
	ret_boolValue = false;
    }
    
    return ret_boolValue;
    
} // bool popen_cplusplus (...)

