//#include "pch.h"
#include "Str.h"
#include <regex>
#include <algorithm>

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
bool FoundLexExpr(const string& lexicalExpressionOrString, const string str) {
    regex expr(lexicalExpressionOrString);
    return regex_search(str, expr);
}

///
/// @brief FindLexExprMatches - returns all the matches of the lexical expression found in the string.
/// @param lexicalExpression The lexical expression to look for in the string.
/// @param str The string to search.
/// @remark FindLexExprMatches("[0-9]+", "abc 12, alpha 34 ,,5678XYZ");
/// @remark returns "12", "34", "5678"
/// @return vector<string> of results
///
vector<string> FindLexExprMatches(const string& lexicalExpression, const string str) {
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

} // end namespace Tau
