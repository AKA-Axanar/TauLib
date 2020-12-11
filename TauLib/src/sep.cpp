#include "sep.h"
#include <string>

using namespace std;

///
/// @file
/// @brief cpp file for directory path seprarator tool.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///

namespace Tau { // to avoid conflict with other libraries

//*******************************
// append path separator helper function
// example:  somepath is a string of a path but you do not know for sure if there is a "/" at the end or not
// somepath + sep + "font" + sep + "default.ttf" will append the separator to somepath only if it's not there
//*******************************
string operator + (const string& leftside, Sep) {
    string ret = leftside;
    ret += sep;     // += only appends if needed

    return ret;
}

//*******************************
// append path separator helper function
// to use "operator +" below, "path + sep" will append the separator only if it's not already on the end of path
//*******************************
void operator += (std::string& leftside, Sep) {
    if (leftside.size() > 0)
    {
        char lastChar = leftside.back();
        if (lastChar != '/' && lastChar != '\\')        // handle either linux or windows path separator being on the end
            leftside += separator; // add separator for this OS at end
    }
}

//
// fixPathSeparators
// changes any / or \ in the string to be the preferred path separator for the OS
//
std::string fixPathSeparators(const std::string& str) {
    filesystem::path p(str);
    p.make_preferred();
    return p.string();
}

//
// fixPathSeparators
// changes any / or \ in the string to be the preferred path separator for the OS
// modifies the passed pathStr.
//
void fixPathSeparators(std::string* str)
    { *str = fixPathSeparators(*str); }

} // end namespace Tau
