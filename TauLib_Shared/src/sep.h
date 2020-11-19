#pragma once

#include "TauLib.h"
#include <string>
#include <vector>

namespace Tau {

//*******************************
// separator
//*******************************
#ifdef __linux__ 
    static const char separator = '/';
#elif _WIN32
    static const char separator = '\\';
#else
    #error unknown OS
#endif

//*******************************
// append separator helper function
//*******************************
struct TAULIBDLL_API Sep { };
const TAULIBDLL_API Sep sep;  // use sep in your code

// example:  somepath is a string of a path but you do not know for sure if there is or is not a "/" at the end or not
// somepath + sep + "font" + sep + "default.ttf" will append the separator to somepath only if it's not there
std::string TAULIBDLL_API operator + (const std::string& leftside, Sep);
void TAULIBDLL_API operator += (std::string& leftside, Sep);

}
