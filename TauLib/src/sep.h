#pragma once

///
/// @file
/// @brief Header file for directory path seprarator tool.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///

/// @todo should detect either / or \ at end of path

#include "TauLib.h"
#include "Str.h"
#include <filesystem>

/// @brief namespace Tau - avoid conflict with other libraries
namespace Tau { // to avoid conflict with other libraries

//*******************************
// separator
//*******************************
inline static const char separator = std::filesystem::path::preferred_separator;
inline static const wchar_t wseparator = std::filesystem::path::preferred_separator;

//*******************************
// line ending
//*******************************
#if defined(_WIN32)
    inline static const char* lineEnding = "\r\n";
#else
    inline static const char* lineEnding = "\n";
#endif

///
/// @brief Sep - append path separator helper function
///
struct Sep { };
/// @brief sep - a global Sep object that can be used anywhere to add a '/' or '\' at the end of a path string if needed.
const Sep sep;  // use sep in your code

///
/// @brief string + Sep 
/// @remark somepath is a path string which may or may not have a '/' at the end.  
/// @remark somepath + sep + "font" + sep + "default.ttf" will create "somepath/font/default.ttf" (in the case of Linux OS).
/// @remark to somepath if there isn't one there already.
///
std::string operator + (const std::string& leftside, Sep);

///
/// @brief string += Sep 
/// @remark called by string + Sep to append a separator char or not.
///
void operator += (std::string& leftside, Sep);

///
/// @brief fixPathSeparators
/// @param pathStr - the path string to fix 
/// @remark changes any / or \ in the string to be the preferred path separator for the OS
/// @return the fixed path
///
std::string fixPathSeparators(const std::string& pathStr);
Strings fixPathSeparators(const Strings& pathStrings);

///
/// @brief fixPathSeparators
/// 
/// @param pathStr - pointer to the path string to fix.  pathStr is modified.
/// @remark changes any / or \ in the string to be the preferred path separator for the OS
/// @return none
///
void fixPathSeparators(std::string* pathStr);
void fixPathSeparators(Strings* pathStrings);

} // end namespace Tau
