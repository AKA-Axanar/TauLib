//#include "pch.h"
#include "Str.h"
#include <regex>
#include <algorithm>
#include <iostream>
#include <assert.h>

using namespace std;

///
/// @file
/// @brief cpp file for string routines.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

namespace Tau { // to avoid conflict with other libraries

                //*******************************
                // Strings
                //*******************************
    
///
/// @brief sortStrings - Sorts the passed vector of strings.
/// @param strings vector<string> to be sorted.
/// @return none.
///
void sortStrings(Strings& strings) {
    sort(strings.begin(), strings.end());
}

///
/// @brief sortStringsInsensitive - Does a case insensitive sort of the passed vector of strings.
/// @param strings vector<string> to be case insensitive sorted.
/// @return none.
///
void sortStringsInsensitive(Strings& strings) {
    sort(strings.begin(), strings.end(), [] (string& str1, string& str2) { return lowerCase(str1) < lowerCase(str2); });
}

                //*******************************
                // string trim
                //*******************************

///
/// @brief ltrim - trim the left leading whitespace from a string.
/// @param s string to trim (const& not modified).
/// @return The trimmed string.
///
string ltrim(const string& s) {
    string temp = s;
    ltrim(&temp);
    return temp;
}

///
/// @brief ltrim - trim the left leading whitespace from a string.
/// @param &string to trim (string is modified).
/// @return none
///
void ltrim(string* s) {
    auto itr = s->erase(s->begin(), find_if_not(s->begin(), s->end(), [&] ( char c) { return isspace(c); }));
}

///
/// @brief rtrim - trim the right leading whitespace from a string.
/// @param string to trim (const& not modified).
/// @return The trimmed string.
///
string rtrim(const string& s) {
    string temp = s;
    rtrim(&temp);
    return temp;
}

///
/// @brief rtrim - trim the right leading whitespace from a string.
/// @param &string to trim (string is modified).
/// @return none
///
void rtrim(string* s) {
    s->erase(find_if_not(s->rbegin(), s->rend(), [&](char c) { return isspace(c); }).base(), s->end());
}

///
/// @brief trim - trim both the leading and trailing whitespace from a string.
/// @param string to trim (const& not modified).
/// @return The trimmed string.
///
string trim(const string& s) {
    return rtrim(ltrim(s));
}

///
/// @brief trim - trim both the leading and trailing whitespace from a string.
/// @param &string to trim (string is modified).
/// @return none
///
void trim(string* s) {
    ltrim(s);
    rtrim(s);
}

                //*******************************
                // string case
                //*******************************

///
/// @brief lowerCase - Return the passed string as lower case.
/// @param string to convert to lower case.
/// @return The lower case string.
///
std::string lowerCase(const std::string& _s) {
    string s = _s;
    transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return s;
}

///
/// @brief lowerCase - Convert the passed satring to lower case.
/// @param &string to convert to lower case.
/// @return none
///
void lowerCase(std::string* s) {
    transform(s->begin(), s->end(), s->begin(),
        [](unsigned char c) { return tolower(c); });
}

///
/// @brief upperCase - Return the passed string as upper case.
/// @param string to convert to upper case.
/// @return The upper case string.
///
std::string upperCase(const std::string& _s) {
    string s = _s;
    transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return std::toupper(c); });
    return s;
}

///
/// @brief upperCase - Convert the passed satring to upper case.
/// @param &string to convert to upper case.
/// @return none
///
void upperCase(std::string* s) {
    transform(s->begin(), s->end(), s->begin(),
        [](unsigned char c) { return toupper(c); });
}

                //*******************************
                // string compare
                //*******************************

///
/// @brief icompareBool - Case insensitive string compare.
/// @param str_a Left hand string to compare.
/// @param str_b Right hand string to compare.
/// @return true if lower(str_a) == tolower(str_b)
///
bool icompareBool(const std::string& a, const std::string& b) {
    if (a.length() != b.length())
        return false;   // not the same length

    return std::equal(a.begin(), a.end(), b.begin(),
        [](unsigned char a1, unsigned char b1) { return tolower(a1) == tolower(b1); });
}

///
/// @brief icompareInt - Case insensitive string compare for sorting.
/// @param str_a Left hand string to compare.
/// @param str_b Right hand string to compare.
/// @return -1 if str_a < str_b, 0 if str_a == str_b, +1 if str_a > str_b
///
int icompareInt(const std::string& a, const std::string& b) {
    return _stricmp(a.c_str(), b.c_str());
}

                //*******************************
                // string replace
                //*******************************

///
/// @brief ReplaceSubStrings - Replace all the matching substrings in a string.
/// @param str The string to search.
/// @param fromSubStringOrLexicalExpression The substring or lexical expression to match.
/// @param toSubString The substring to replace the substring with.
/// @return The resulting string.
///
string ReplaceSubStrings(const std::string& str, const std::string& fromSubStringOrLexicalExpression,
    const std::string& toSubString) {
    string result;
    regex from(fromSubStringOrLexicalExpression);
    string to(toSubString);

    regex_replace(back_inserter(result), str.begin(), str.end(), from, to);
    return result;
}

///
/// @brief ReplaceSubStrings - Replace all the matching substrings in a string.
/// @param str The &string to search.  The string is modified.
/// @param fromSubStringOrLexicalExpression The substring or lexical expression to match.
/// @param toSubString The substring to replace the substring with.
/// @return none
///
void ReplaceSubStrings(std::string* str, const std::string& fromSubStringOrLexicalExpression,
    const std::string& toSubString) {
    *str = ReplaceSubStrings(*str, fromSubStringOrLexicalExpression, toSubString);
}

                //*******************************
                // string find
                //*******************************

///
/// @brief FoundLexExpr - returns whether the lexical expression (or plain string) is found in a string.
/// @param lexicalExpressionOrString The string or lexical expression to look for in the string.
/// @param str The string to search.
/// @remark lexical expression = "[A-Za-z0-9]+"
/// @remark lexical expression = "FindMe"
/// @return true or false
///
bool FoundLexExpr(const string& lexicalExpressionOrString, const string& str) {
    regex expr(lexicalExpressionOrString);
    return regex_search(str, expr);
}

///
/// @brief IsLexExpr - returns whether the string matches exactly the lexical expression (or plain string).
/// @param lexicalExpressionOrString The string or lexical expression to look for in the string.
/// @param str The string to search.
/// @remark lexical expression = "[A-Za-z0-9]+"
/// @remark lexical expression = "FindMe"
/// @return true or false
/// @note To test if the string exactly matches the leical expression "^" is prefixed nd "$" is postfixed to the string.
/// For example, if "[A-Za-z0-9]+" is passed, it searches for "^[A-Za-z0-9]+$"
///
bool IsLexExpr(const std::string& lexicalExpressionOrString, const std::string& str) {
    return FoundLexExpr("^" + lexicalExpressionOrString + "$", str);
}

static string Int_LexExpr{ "[+-]?[\\d]+" };
static string Float_LexExpr{ "[-+] ? [0 - 9] * \\. ? [0 - 9] + ([eE][-+] ? [0 - 9] + ) ?" };

///
/// @brief IsInt - Returns if the string is an integer.
///
bool IsInt(const string& str) {
    return IsLexExpr(Int_LexExpr, str);
}

///
/// @brief IsFloat - Returns if the string is a float.
///
bool IsFloat(const string& str) {
    return IsLexExpr(Float_LexExpr, str);
}

///
/// @brief FindLexExprMatches - returns all the matches of the lexical expression found in the string.
/// @param lexicalExpression The lexical expression to look for in the string.
/// @param str The string to search.
/// @remark FindLexExprMatches("[0-9]+", "abc 12, alpha 34 ,,5678XYZ");
/// @remark returns "12", "34", "5678"
/// @return vector<string> of results
///
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

///
/// @brief FindLexExprMatch - returns a match of the lexical expression if found in the string.
/// @param lexicalExpression The lexical expression to look for in the string.
/// @param str The string to search.
/// @return string of a match.  "" if none.
///
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

///
/// @brief SplitStringAtChars - returns the string pieces after splitting the string at the passed char or chars.
/// @param str The string to split.
/// @param splitAt The char or chars to split the string at.
/// @return vector<string> of results
///
Strings SplitStringAtChars(const string& str, const string& splitAt, bool trimTheWhitespaceFromThePieces) {
    string expr = "[^" + splitAt + "\n\r]+";
    Strings temp = FindLexExprMatches(expr, str);
    if (trimTheWhitespaceFromThePieces)
        for_each(begin(temp), end(temp), [&](string& s) { trim(&s); });

    return temp;
}

///
/// @brief SplitStringAtCommas - returns the string pieces after splitting the string at the commas.
/// @param str The string to split.
/// @return vector<string> of results
///
Strings SplitStringAtCommas(const std::string& str, bool trimTheWhitespaceFromThePieces)
{
    return SplitStringAtChars(str, ",", trimTheWhitespaceFromThePieces);
}

///
/// @brief CommaSepStringToInts - Takes a comma separated string of int's and returns a vector of int's.
/// @param str The string of comma separated int's.
/// @return vector<int> of the int's.
///
vector<int> CommaSepStringToInts(const string& str) {
    auto strings = SplitStringAtCommas(str);
    vector<int> ret;
    for (const auto& s : strings) {
        if (IsLexExpr(Int_LexExpr, s))
            ret.emplace_back(stoi(s));
        else {
            assert(false);
            cerr << "CommaSepStringToInts: invalid integer in '" << str << "'" << endl;
        }
    }

    return ret;
}

///
/// @brief CommaSepStringToFloats - Takes a comma separated string of floats and returns a vector of floats.
/// @param str The string of comma separated floats.
/// @return vector<int> of the floats.
///
vector<float> CommaSepStringToFloats(const string& str) {
    auto strings = SplitStringAtCommas(str);
    vector<float> ret;
    for (const auto& s : strings) {
        if (IsLexExpr(Int_LexExpr, s))
            ret.emplace_back(stof(s));
        else {
            assert(false);
            cerr << "CommaSepStringToInts: invalid float in '" << str << "'" << endl;
        }
    }

    return ret;
}

///
/// @brief CommaSepStringToDoubles - Takes a comma separated string of Doubles and returns a vector of Doubles.
/// @param str The string of comma separated Doubles.
/// @return vector<int> of the Doubles.
///
vector<double> CommaSepStringToDoubles(const string& str) {
    auto strings = SplitStringAtCommas(str);
    vector<double> ret;
    for (const auto& s : strings) {
        if (IsLexExpr(Int_LexExpr, s))
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

///
/// @brief RemoveCharFromString - removes all instances of a char from the string
/// @param str The string to search
/// @param ch The char remove.
/// @return none
///
void RemoveCharFromString(string* str, char ch) {
    str->erase( remove(str->begin(), str->end(), ch), str->end() );
}

///
/// @brief RemoveCharFromString - removes all instances of a char from the string
/// @param str The string to search
/// @param ch The char remove.
/// @return The string with the chars removed
///
string RemoveCharFromString(const string& str, char ch) {
    string temp = str;
    RemoveCharFromString(&temp, ch);
    return temp;
}

///
/// @brief RemoveMultipleCharsFromString - removes all instances of multiple chars from the string
/// @param str The string to search
/// @param charsToRemove The characters to be removed.
/// @return none
///
void RemoveMultipleCharsFromString(string* str, const string& charsToRemove) {
    auto matchFound = [&](char c) {
        return charsToRemove.find(c) != string::npos; // return if the char is to be removed
    };

    str->erase( remove_if(str->begin(), str->end(), matchFound), str->end() );
}

///
/// @brief RemoveMultipleCharsFromString - removes all instances of multiple chars from the string
/// @param str The string to search
/// @param charsToRemove The characters to be removed.
/// @return The string with those characters removed.
///
string RemoveMultipleCharsFromString(const string& str, const string& charsToRemove) {
    string temp = str;
    RemoveMultipleCharsFromString(&temp, charsToRemove);
    return temp;
}

///
/// @brief RemoveCRLFCharsFromEndOfString - removes any CR or LF chars from the end of the string.
/// @param str The string to search and modify
/// @return none
///
void RemoveCRLFCharsFromEndOfString(std::string* str) {
    while (!str->empty() && (*str->rbegin() == '\r' || *str->rbegin() == '\n'))
        str->erase(str->length()-1, 1);
}

///
/// @brief RemoveCRLFCharsFromEndOfString - removes any CR or LF chars from the end of the string.
/// @param str The string to search
/// @return The string with CR and LF's removed.
///
std::string RemoveCRLFCharsFromEndOfString(const std::string& str) {
    string temp = str;
    RemoveCRLFCharsFromEndOfString(&temp);
    return temp;
}

} // end namespace Tau
