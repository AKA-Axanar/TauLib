#include "pch.h"
#include "Str.h"

using namespace std;

namespace Tau {

//
// ltrim.  trim the left leading whitespace.
//
string ltrim(const string& s) {
    string temp = s;
    ltrim(&temp);
    return temp;
}
void ltrim(string* s) {
    auto ch = *find_if_not(s->begin(), s->end(), isspace);
    auto itr = s->erase(s->begin(), find_if_not(s->begin(), s->end(), isspace));
}

//
// rtrim.  trim the right trailing whitespace.
//
string rtrim(const string& s) {
    string temp = s;
    rtrim(&temp);
    return temp;
}
void rtrim(string* s) {
    s->erase(find_if_not(s->rbegin(), s->rend(), isspace).base(), s->end());
}

//
// trim.  trim the left and right whitespace.
//
string trim(const string& s) {
    return rtrim(ltrim(s));
}
void trim(string* s) {
    ltrim(s);
    rtrim(s);
}

//
// lowerCase
//
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

//
// upperCase
//
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

//
// icompareBool - case insensitive compare.  returns a bool
//
bool icompareBool(const std::string& a, const std::string& b) {
    if (a.length() != b.length())
        return false;   // not the same length

    return std::equal(a.begin(), a.end(), b.begin(),
        [](unsigned char a1, unsigned char b1) { return tolower(a1) == tolower(b1); });
}

//
// icompareInt - case insensitive compare.  returns an int (-1, 0, 1)
//
int icompareInt(const std::string& a, const std::string& b) {
    return _stricmp(a.c_str(), b.c_str());
}

} // end namespace Tau
