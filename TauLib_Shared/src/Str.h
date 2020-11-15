#pragma once

#include <string>
#include <algorithm>
#include "TauLib.h"

namespace Tau {

//
// ltrim.  trim the left leading whitespace.
//
void TAULIBDLL_API ltrim(std::string* s);
std::string ltrim(const std::string& s);

//
// rtrim.  trim the right trailing whitespace.
//
void TAULIBDLL_API rtrim(std::string* s);
std::string rtrim(const std::string& s);

//
// trim.  trim the left and right whitespace.
//
void TAULIBDLL_API trim(std::string* s);
std::string trim(const std::string& s);

//
// lowerCase
//
void TAULIBDLL_API lowerCase(std::string* s);
std::string lowerCase(const std::string& _s);

//
// upperCase
//
void TAULIBDLL_API upperCase(std::string* s);
std::string upperCase(const std::string& _s);

//
// icompareBool - case insensitive compare.  returns a bool
//
bool TAULIBDLL_API icompareBool(const std::string& a, const std::string& b);

//
// icompareInt - case insensitive compare.  returns an int (-1, 0, 1)
//
int TAULIBDLL_API icompareInt(const std::string& a, const std::string& b);
}