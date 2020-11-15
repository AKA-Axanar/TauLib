#pragma once

#include <string>
#include <algorithm>
#include "TauLib.h"

namespace Tau {

//
// ltrim.  trim the left leading whitespace.
//
std::string TAULIBDLL_API ltrim(const std::string& s);
void TAULIBDLL_API ltrim(std::string* s);

//
// rtrim.  trim the right trailing whitespace.
//
std::string TAULIBDLL_API rtrim(const std::string& s);
void TAULIBDLL_API rtrim(std::string* s);

//
// trim.  trim the left and right whitespace.
//
std::string TAULIBDLL_API trim(const std::string& s);
void TAULIBDLL_API trim(std::string* s);

//
// lowerCase
//
std::string TAULIBDLL_API lowerCase(const std::string& _s);
void TAULIBDLL_API lowerCase(std::string* s);

//
// upperCase
//
std::string TAULIBDLL_API upperCase(const std::string& _s);
void TAULIBDLL_API upperCase(std::string* s);

//
// icompareBool - case insensitive compare.  returns a bool
//
bool TAULIBDLL_API TAULIBDLL_API icompareBool(const std::string& a, const std::string& b);

//
// icompareInt - case insensitive compare.  returns an int (-1, 0, 1)
//
int TAULIBDLL_API TAULIBDLL_API icompareInt(const std::string& a, const std::string& b);
}