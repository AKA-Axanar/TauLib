//#include "pch.h"
#include "Str.h"
#include <regex>
#include <algorithm>

using namespace std;

namespace Tau {

void sortStrings(Strings& strings) {
    sort(strings.begin(), strings.end());
}

void sortStringsInsensitive(Strings& strings) {
    sort(strings.begin(), strings.end(), [] (string& str1, string& str2) { return lowerCase(str1) < lowerCase(str2); });
}

//*******************************
// ltrim.  trim the left leading whitespace.
//*******************************
string ltrim(const string& s) {
    string temp = s;
    ltrim(&temp);
    return temp;
}
void ltrim(string* s) {
    auto itr = s->erase(s->begin(), find_if_not(s->begin(), s->end(), [&] ( char c) { return isspace(c); }));
}

//*******************************
// rtrim.  trim the right trailing whitespace.
//*******************************
string rtrim(const string& s) {
    string temp = s;
    rtrim(&temp);
    return temp;
}
void rtrim(string* s) {
    s->erase(find_if_not(s->rbegin(), s->rend(), [&](char c) { return isspace(c); }).base(), s->end());
}

//*******************************
// trim.  trim the left and right whitespace.
//*******************************
string trim(const string& s) {
    return rtrim(ltrim(s));
}
void trim(string* s) {
    ltrim(s);
    rtrim(s);
}

//*******************************
// lowerCase
//*******************************
std::string lowerCase(const std::string& _s) {
    string s = _s;
    transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return s;
}
void lowerCase(std::string* s) {
    transform(s->begin(), s->end(), s->begin(),
        [](unsigned char c) { return tolower(c); });
}

//*******************************
// upperCase
//*******************************
std::string upperCase(const std::string& _s) {
    string s = _s;
    transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return std::toupper(c); });
    return s;
}
void upperCase(std::string* s) {
    transform(s->begin(), s->end(), s->begin(),
        [](unsigned char c) { return toupper(c); });
}

//*******************************
// icompareBool - case insensitive compare.  returns a bool
//*******************************
bool icompareBool(const std::string& a, const std::string& b) {
    if (a.length() != b.length())
        return false;   // not the same length

    return std::equal(a.begin(), a.end(), b.begin(),
        [](unsigned char a1, unsigned char b1) { return tolower(a1) == tolower(b1); });
}

//*******************************
// icompareInt - case insensitive compare.  returns an int (-1, 0, 1)
//*******************************
int icompareInt(const std::string& a, const std::string& b) {
    return _stricmp(a.c_str(), b.c_str());
}

//*******************************
// ReplaceSubStrings
//*******************************
string ReplaceSubStrings(const std::string& str, const std::string& fromSubStringOrLexicalExpression,
    const std::string& toSubString) {
    string result;
    regex from(fromSubStringOrLexicalExpression);
    string to(toSubString);

    regex_replace(back_inserter(result), str.begin(), str.end(), from, to);
    return result;
}
void ReplaceSubStrings(std::string* str, const std::string& fromSubStringOrLexicalExpression,
    const std::string& toSubString) {
    *str = ReplaceSubStrings(*str, fromSubStringOrLexicalExpression, toSubString);
}

//*******************************
// FoundLexExpr
// returns whether the lexical expression (or plain string) is found in a string.
// example lexical expression = "[A-Za-z0-9]+"
// example lexical expression = "FindMe"
//*******************************
bool FoundLexExpr(const string& lexicalExpressionOrString, const string str) {
    regex expr(lexicalExpressionOrString);
    return regex_search(str, expr);
}

//*******************************
// FindLexExprMatches
// returns all the matches of the lexical expression found in the string
// example: FindLexExprMatches("[0-9]+", "abc 12, alpha 34 ,,5678XYZ");
// returns "12", "34", "5678"
//*******************************
vector<string> FindLexExprMatches(const string& lexicalExpressionOrString, const string str) {
    regex expr(lexicalExpressionOrString);
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
