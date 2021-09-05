//
// string routines
// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
// 

//#include "pch.h"
#include "Str.h"
#include <regex>
#include <algorithm>
#include <iostream>
#include <assert.h>

using namespace std;

namespace Tau { // to avoid conflict with other libraries

                //*******************************
                // Strings
                //*******************************
    
//
// sortStrings - Sorts the passed vector of strings.
//
void sortStrings(Strings& strings) {
    sort(strings.begin(), strings.end());
}

//
// sortStringsInsensitive - Does a case insensitive sort of the passed vector of strings.
//
void sortStringsInsensitive(Strings& strings) {
    sort(strings.begin(), strings.end(), [] (string& str1, string& str2) { return lowerCase(str1) < lowerCase(str2); });
}

                //*******************************
                // string trim
                //*******************************

//
// ltrim - trim the left leading whitespace from a string.
// returns The trimmed string.
//
string ltrim(const string& s) {
    string temp = s;
    ltrim(&temp);
    return temp;
}

//
// ltrim - trim the left leading whitespace from a string.
//
void ltrim(string* s) {
    auto itr = s->erase(s->begin(), find_if_not(s->begin(), s->end(), [&] ( char c) { return isspace(c); }));
}

//
// rtrim - trim the right leading whitespace from a string.
// return The trimmed string.
//
string rtrim(const string& s) {
    string temp = s;
    rtrim(&temp);
    return temp;
}

//
// rtrim - trim the right leading whitespace in the passed string string.
// return none
//
void rtrim(string* s) {
    s->erase(find_if_not(s->rbegin(), s->rend(), [&](char c) { return isspace(c); }).base(), s->end());
}

//
// trim - trim both the leading and trailing whitespace from a string.
// returns The trimmed string.
//
string trim(const string& s) {
    return rtrim(ltrim(s));
}

//
// trim - trim both the leading and trailing whitespace from a string.
//
void trim(string* s) {
    ltrim(s);
    rtrim(s);
}

                //*******************************
                // string case
                //*******************************

//
// lowerCase - Return the passed string as lower case.
// returns The lower case string.
//
std::string lowerCase(const std::string& _s) {
    string s = _s;
    transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return s;
}

//
// lowerCase - Convert the passed string to lower case.
// return none
//
void lowerCase(std::string* s) {
    transform(s->begin(), s->end(), s->begin(),
        [](unsigned char c) { return tolower(c); });
}

//
// upperCase - Return the passed string as upper case.
// returns The upper case string.
//
std::string upperCase(const std::string& _s) {
    string s = _s;
    transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return std::toupper(c); });
    return s;
}

//
// upperCase - Convert the passed string to upper case.
//
void upperCase(std::string* s) {
    transform(s->begin(), s->end(), s->begin(),
        [](unsigned char c) { return toupper(c); });
}

                //*******************************
                // string compare
                //*******************************

//
// icompareBool - Case insensitive string compare.
//
bool icompareBool(const std::string& a, const std::string& b) {
    if (a.length() != b.length())
        return false;   // not the same length

    return std::equal(a.begin(), a.end(), b.begin(),
        [](unsigned char a1, unsigned char b1) { return tolower(a1) == tolower(b1); });
}

//
// icompareInt - Case insensitive string compare for sorting.
// return -1 if str_a < str_b, 0 if str_a == str_b, +1 if str_a > str_b
//
int icompareInt(const std::string& a, const std::string& b) {
    return _stricmp(a.c_str(), b.c_str());
}

//
// sortStringCompare - Compare two strings (for lambdas).
//
bool sortStringCompare(const std::string& string1, const std::string& string2) {
    return string1 < string2;
}

//
// sortStringCompareInsensitive - Compare two strings (for lambdas).
//
bool sortStringCompareInsensitive(const std::string& string1, const std::string& string2) {
    return lowerCase(string1) < lowerCase(string2);
}

                //*******************************
                // string replace
                //*******************************

//
// ReplaceSubStrings - Replace all the matching substrings in a string.
// return The resulting string.
//
string ReplaceSubStrings(const std::string& str, const std::string& fromSubStringOrLexicalExpression,
    const std::string& toSubString) {
    string result;
    regex from(fromSubStringOrLexicalExpression);
    string to(toSubString);

    regex_replace(back_inserter(result), str.begin(), str.end(), from, to);
    return result;
}

//
// ReplaceSubStrings - Replace all the matching substrings in the passed string.
// return none
//
void ReplaceSubStrings(std::string* str, const std::string& fromSubStringOrLexicalExpression,
    const std::string& toSubString) {
    *str = ReplaceSubStrings(*str, fromSubStringOrLexicalExpression, toSubString);
}

                //*******************************
                // string find
                //*******************************

//
// FoundLexExpr - returns whether the lexical expression (or plain string) is found in a string.
// @param lexicalExpressionOrString The string or lexical expression to look for in the string.
// ex: lexical expression = "[A-Za-z0-9]+"
// ex: lexical expression = "FindMe"
// return true or false
//
bool FoundLexExpr(const string& lexicalExpressionOrString, const string& str) {
    regex expr(lexicalExpressionOrString);
    return regex_search(str, expr);
}

//
// IsLexExpr - returns whether the string matches exactly the lexical expression (or plain string).
// lexicalExpressionOrString - The string or lexical expression to look for in the string.
// str - The string to search.
// ex: lexical expression = "[A-Za-z0-9]+"
// ex: lexical expression = "FindMe"
// return true or false
// note: To test if the string exactly matches the leical expression "^" is prefixed nd "$" is postfixed to the string.
// For example, if "[A-Za-z0-9]+" is passed, it searches for "^[A-Za-z0-9]+$"
//
bool IsLexExpr(const std::string& lexicalExpressionOrString, const std::string& str) {
    return FoundLexExpr("^" + lexicalExpressionOrString + "$", str);
}

static string Int_LexExpr{ "[+-]?[\\d]+" };
static string Float_LexExpr{ "[-+] ? [0 - 9] * \\. ? [0 - 9] + ([eE][-+] ? [0 - 9] + ) ?" };

//
// IsInt - Returns if the string is an integer.
//
bool IsInt(const string& str) {
    return IsLexExpr(Int_LexExpr, str);
}

//
// IsFloat - Returns if the string is a float.
//
bool IsFloat(const string& str) {
    return IsLexExpr(Float_LexExpr, str);
}

//
// FindLexExprMatches - returns all the matches of the lexical expression found in the string.
// lexicalExpression - The lexical expression to look for in the string.
// str - The string to search.
// ex: FindLexExprMatches("[0-9]+", "abc 12, alpha 34 ,,5678XYZ");
//     returns "12", "34", "5678"
// returns vector<string> of results
//
Strings FindLexExprMatches(const string& lexicalExpression, const string& str) {
    regex expr(lexicalExpression);
    smatch match;
    regex_match(str, match, expr);

    vector<string> ret;
    string temp = str;
    while (regex_search(temp, match, expr)) {
        for (auto m:match)
            ret.emplace_back(m);
        temp = match.suffix().str();
    }

    return ret;
}

//
// FindLexExprMatch - returns a match of the lexical expression if found in the string.
// lexicalExpression - The lexical expression to look for in the string.
// str - The string to search.
// returns the string of a match.  "" if none.
//
string FindLexExprMatch(const std::string& lexicalExpression, const std::string& str) {
    regex expr(lexicalExpression);
    smatch match;
    if (regex_search(str, match, expr))
        return match.str();
    else
        return "";
}

//*******************************
// split string
//*******************************

//
// SplitStringAtChars - returns the string pieces after splitting the string at the passed char or chars.
// returns vector<string> of results
//
Strings SplitStringAtChars(const string& str, const string& splitAt, bool trimTheWhitespaceFromThePieces) {
    string expr = "[^" + splitAt + "\n\r]+";
    Strings temp = FindLexExprMatches(expr, str);
    if (trimTheWhitespaceFromThePieces)
        for_each(begin(temp), end(temp), [&](string& s) { trim(&s); });

    return temp;
}

//
// SplitStringAtCommas - returns the string pieces after splitting the string at the commas.
// returns vector<string> of results
//
Strings SplitStringAtCommas(const std::string& str, bool trimTheWhitespaceFromThePieces)
{
    return SplitStringAtChars(str, ",", trimTheWhitespaceFromThePieces);
}

//
// CommaSepStringToInts - Takes a comma separated string of int's and returns a vector of int's.
// str - The string of comma separated int's.
// returns vector<int> of the int's.
//
vector<int> CommaSepStringToInts(const string& str) {
    auto strings = SplitStringAtCommas(str);
    vector<int> ret;
    for (const auto& s : strings) {
        if (IsInt(s))
            ret.emplace_back(stoi(s));
        else {
            assert(false);
            cerr << "CommaSepStringToInts: invalid integer in '" << str << "'" << endl;
        }
    }

    return ret;
}

//
// CommaSepStringToFloats - Takes a comma separated string of floats and returns a vector of floats.
// str - The string of comma separated floats.
// returns vector<int> of the floats.
//
vector<float> CommaSepStringToFloats(const string& str) {
    auto strings = SplitStringAtCommas(str);
    vector<float> ret;
    for (const auto& s : strings) {
        if (IsFloat(s))
            ret.emplace_back(stof(s));
        else {
            assert(false);
            cerr << "CommaSepStringToInts: invalid float in '" << str << "'" << endl;
        }
    }

    return ret;
}

//
// CommaSepStringToDoubles - Takes a comma separated string of Doubles and returns a vector of Doubles.
// str - The string of comma separated Doubles.
// returns vector<int> of the Doubles.
//
vector<double> CommaSepStringToDoubles(const string& str) {
    auto strings = SplitStringAtCommas(str);
    vector<double> ret;
    for (const auto& s : strings) {
        if (IsFloat(s))
            ret.emplace_back(stod(s));
        else {
            assert(false);
            cerr << "CommaSepStringToInts: invalid double in '" << str << "'" << endl;
        }
    }

    return ret;
}

                //*******************************
                // string remove
                //*******************************

//
// RemoveCharFromString - removes all instances of a char from the string
// str - The string to search
// ch - The char remove.
// return none
//
void RemoveCharFromString(string* str, char ch) {
    str->erase( remove(str->begin(), str->end(), ch), str->end() );
}

//
// RemoveCharFromString - removes all instances of a char from the string
// str - The string to search
// ch - The char remove.
// returns The string with the chars removed
//
string RemoveCharFromString(const string& str, char ch) {
    string temp = str;
    RemoveCharFromString(&temp, ch);
    return temp;
}

//
// RemoveMultipleCharsFromString - removes all instances of multiple chars from the string
// str - The string to search
// charsToRemove - The characters to be removed.
// return none
//
void RemoveMultipleCharsFromString(string* str, const string& charsToRemove) {
    auto matchFound = [&](char c) {
        return charsToRemove.find(c) != string::npos; // return if the char is to be removed
    };

    str->erase( remove_if(str->begin(), str->end(), matchFound), str->end() );
}

//
// RemoveMultipleCharsFromString - removes all instances of multiple chars from the string
// str - The string to search
// charsToRemove - The characters to be removed.
// returns The string with those characters removed.
//
string RemoveMultipleCharsFromString(const string& str, const string& charsToRemove) {
    string temp = str;
    RemoveMultipleCharsFromString(&temp, charsToRemove);
    return temp;
}

//
// RemoveCRLFCharsFromEndOfString - removes any CR or LF chars from the end of the string.
// str - The string to search and modify
// return none
//
void RemoveCRLFCharsFromEndOfString(std::string* str) {
    while (!str->empty() && (*str->rbegin() == '\r' || *str->rbegin() == '\n'))
        str->erase(str->length()-1, 1);
}

//
// RemoveCRLFCharsFromEndOfString - removes any CR or LF chars from the end of the string.
// str - The string to search
// returns The string with CR and LF's removed.
//
std::string RemoveCRLFCharsFromEndOfString(const std::string& str) {
    string temp = str;
    RemoveCRLFCharsFromEndOfString(&temp);
    return temp;
}

                //*******************************
                // string misc
                //*******************************

//
// DoubleQuoteStringIfSpace - if there is a space in the string, add a double quote to the front and back
// 
std::string DoubleQuoteStringIfSpace(const string& s) {
    string temp = s;
    if (!temp.empty() && temp.find(" ") != string::npos) {
        if (temp.front() != '"')
            temp.insert(begin(temp), '"');
        if (temp.back() != '"')
            temp.insert(end(temp), '"');
    };

    return temp;
}

//
// DoubleQuoteStringIfSpace - if there is a space in the string, add a double quote to the front and back
// 
void DoubleQuoteStringIfSpace(std::string* s) {
    *s = DoubleQuoteStringIfSpace(*s);
}

//
// isBlank - true if empty string or only whitespace
// 
bool isBlank(const std::string s) {
    return ltrim(s).size() == 0;
}

//
// isComment - true if first non-whitespace char is comment char ch
// 
bool isComment(const std::string s, char ch) {
    string temp = ltrim(s); // remove leading whitespace
    if (temp.size() == 0)
        return true;    // blank line

    // true if now begins with ch
    return (temp[0] == ch);
}

} // end namespace Tau
