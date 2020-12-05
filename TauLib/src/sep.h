#pragma once

/**
 *  @file
 *
 *  Header file for directory path seprarator tool.
 *
 */

#include "TauLib.h"
#include <string>
#include <filesystem>

using namespace std;

/**
 *  \brief avoid conflict with other libraries
 */
namespace Tau { // to avoid conflict with other libraries

//*******************************
// separator
//*******************************
static const char separator = std::filesystem::path::preferred_separator;
static const wchar_t wseparator = std::filesystem::path::preferred_separator;


//*******************************
// append path separator helper function
//*******************************
struct Sep { };
const Sep sep;  // use sep in your code

// example:  somepath is a string of a path but you do not know for sure if there is a "/" at the end or not
// somepath + sep + "font" + sep + "default.ttf" will append the separator to somepath only if it's not there
std::string operator + (const std::string& leftside, Sep);
void operator += (std::string& leftside, Sep);

//
// fixPathSeparators
// changes any / or \ in the string to be the preferred path separator for the OS
//
std::string fixPathSeparators(const std::string& str);
void fixPathSeparators(std::string* str);

} // end namespace Tau
