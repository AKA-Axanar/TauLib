#pragma once

#include <string>
#include <vector>
#include "TauLib.h"

namespace Tau {

using Strings = std::vector<std::string>;

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
bool TAULIBDLL_API icompareBool(const std::string& a, const std::string& b);

//
// icompareInt - case insensitive compare.  returns an int (-1, 0, 1)
//
int TAULIBDLL_API icompareInt(const std::string& a, const std::string& b);

//
// ReplaceSubStrings
//
std::string TAULIBDLL_API ReplaceSubStrings(const std::string& str, const std::string& fromSubStringOrLexicalExpression,
    const std::string& toSubString);
void TAULIBDLL_API ReplaceSubStrings(std::string* str, const std::string& fromSubStringOrLexicalExpression,
    const std::string& toSubString);

//
// FoundLexExpr
// returns whether the lexical expression (or plain string) is found in a string.
// example lexical expression = "[A-Za-z0-9]+"
// example lexical expression = "FindMe"
//
bool TAULIBDLL_API FoundLexExpr(const std::string& lexicalExpressionOrString, const std::string str);

//
// FindLexExprMatches
// returns all the matches of the lexical expression found in the string
// example: FindLexExprMatches("[0-9]+", "abc 12, alpha 34 ,,5678XYZ");
// returns "12", "34", "5678"
//
std::vector<std::string> TAULIBDLL_API FindLexExprMatches(const std::string& lexicalExpressionOrString, const std::string str);

} // end namespace Tau
