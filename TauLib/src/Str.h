#pragma once

#include <string>
#include <vector>
#include "TauLib.h"

namespace Tau { // too avoid conflict with other libraries

//*******************************
// Strings
//*******************************
    
using Strings = std::vector<std::string>;

void sortStrings(Strings& strings);
void sortStringsInsensitive(Strings& strings);

//*******************************
// string routines
//*******************************

//*******************************
// ltrim.  trim the left leading whitespace.
//*******************************
std::string ltrim(const std::string& s);
void ltrim(std::string* s);

//*******************************
// rtrim.  trim the right trailing whitespace.
//*******************************
std::string rtrim(const std::string& s);
void rtrim(std::string* s);

//*******************************
// trim.  trim the left and right whitespace.
//*******************************
std::string trim(const std::string& s);
void trim(std::string* s);

//*******************************
// lowerCase
//*******************************
std::string lowerCase(const std::string& _s);
void lowerCase(std::string* s);

//*******************************
// upperCase
//*******************************
std::string upperCase(const std::string& _s);
void upperCase(std::string* s);

//*******************************
// icompareBool - case insensitive compare.  returns a bool
//*******************************
bool icompareBool(const std::string& a, const std::string& b);

//*******************************
// icompareInt - case insensitive compare.  returns an int (-1, 0, 1)
//*******************************
int icompareInt(const std::string& a, const std::string& b);

//*******************************
// ReplaceSubStrings
//*******************************
std::string ReplaceSubStrings(const std::string& str, const std::string& fromSubStringOrLexicalExpression,
    const std::string& toSubString);
void ReplaceSubStrings(std::string* str, const std::string& fromSubStringOrLexicalExpression,
    const std::string& toSubString);

//*******************************
// FoundLexExpr
// returns whether the lexical expression (or plain string) is found in a string.
// example lexical expression = "[A-Za-z0-9]+"
// example lexical expression = "FindMe"
//*******************************
bool FoundLexExpr(const std::string& lexicalExpressionOrString, const std::string str);

//*******************************
// FindLexExprMatches
// returns all the matches of the lexical expression found in the string
// example: FindLexExprMatches("[0-9]+", "abc 12, alpha 34 ,,5678XYZ");
// returns "12", "34", "5678"
//*******************************
std::vector<std::string> FindLexExprMatches(const std::string& lexicalExpressionOrString, const std::string str);

} // end namespace Tau
