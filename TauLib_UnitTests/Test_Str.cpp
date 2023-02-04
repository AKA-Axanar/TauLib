#include "pch.h"
#include "Str.h"
#include "Sep.h"

using namespace std;
using namespace Tau;

//
// test string trim routines.
//
TEST(TestStr, TestStr_trim) {
    string temp;
    string ret;

    temp = "  abc  ";
    ltrim(&temp);
    EXPECT_EQ(temp, "abc  ");

    temp = "  abc  ";
    rtrim(&temp);
    EXPECT_EQ(temp, "  abc");

    ret = ltrim("  abc  ");
    EXPECT_EQ(ret, "abc  ");

    ret = rtrim("  abc  ");
    EXPECT_EQ(ret, "  abc");
}

//
// test string lower and uppoer case conversion routines.
//
TEST(TestStr, TestStr_case) {
    string temp;
    string ret;

    temp = "Alpha Beta";
    lowerCase(&temp);
    EXPECT_EQ(temp, "alpha beta");

    temp = "Alpha Beta";
    upperCase(&temp);
    EXPECT_EQ(temp, "ALPHA BETA");

    temp = "Alpha Beta";
    ret = lowerCase(temp);
    EXPECT_EQ(ret, "alpha beta");

    temp = "Alpha Beta";
    ret = upperCase(temp);
    EXPECT_EQ(ret, "ALPHA BETA");
}

//
// test string case insensitive compares
//
TEST(TestStr, TestStr_compare) {
    EXPECT_EQ(icompareBool("Alpha", "alpha"), true);
    EXPECT_EQ(icompareBool("Alpha", "Beta"), false);

    EXPECT_EQ(icompareInt("Alpha", "Beta"), -1);
    EXPECT_EQ(icompareInt("Alpha", "alpha"), 0);
    EXPECT_EQ(icompareInt("Beta", "Alpha"), 1);
}

//
// test regex string functions
//
TEST(TestStr, TestStr_regex) {
    EXPECT_EQ(ReplaceSubString("abcdefabcdef", "abc", "XXX"), "XXXdefXXXdef");
    string temp = "abcdefabcdef";
    ReplaceSubString(&temp, "abc", "XXX");
    EXPECT_EQ(temp, "XXXdefXXXdef");

    EXPECT_EQ(FoundLexExpr("[a-z]+", "abcdefabcdef"), true);
    EXPECT_EQ(FoundLexExpr("[0-9]+", "abcdefabcdef"), false);
    EXPECT_EQ(FoundLexExpr("def", "abcdefabcdef"), true);
    auto matches = FindLexExprMatches("[0-9]+", "abc 12, alpha 34 ,,5678XYZ");
    //cout << "count = " << matches.size() << endl;
    EXPECT_EQ(matches.size(), 3);
    if (matches.size() == 3) {
        EXPECT_EQ(matches[0], "12");
        EXPECT_EQ(matches[1], "34");
        EXPECT_EQ(matches[2], "5678");
    }

    string serial = FindLexExprMatch("^[A-Za-z]{4}-[0-9]{5}", "SLUS-00119 # Die Hard Trilogy US (Justifier/Hyperblaster)");
    EXPECT_EQ(serial, "SLUS-00119");

    string s = FindLexExprMatch("^[[:alnum:]]+", "abc123##");
    EXPECT_EQ(s, "abc123");
}

//
// TestStr_split
//
TEST(TestStr, TestStr_split) {
    Strings temp = SplitStringAtCommas("This is, not   , a drill.", true);
    EXPECT_EQ(temp.size(), 3);
    EXPECT_EQ(temp[0], "This is");
    EXPECT_EQ(temp[1], "not");
    EXPECT_EQ(temp[2], "a drill.");
}

//
// test sep
//
TEST(TestStr, TestStr_sep) {
#ifdef __linux__ 
    EXPECT_EQ(string("abc") + sep + "fonts", "abc/fonts");
    EXPECT_EQ(string("abc/") + sep + "fonts", "abc/fonts");     // do I need to use \/f?  is /f a form feed here?
    EXPECT_EQ(string("abc\\") + sep + "fonts", "abc/fonts");    // do I need to use \/f?  is /f a form feed here?
#elif _WIN32
    EXPECT_EQ(string("abc") + sep + "fonts", "abc\\fonts");
    EXPECT_EQ(string("abc\\") + sep + "fonts", "abc\\fonts");
    EXPECT_EQ(string("abc/") + sep + "fonts", "abc\\fonts");
#else
    #error unknown OS
#endif
}

//
// test sep
//
TEST(TestStr, TestStr_fixPathSeparators) {
#ifdef __linux__ 
    string str1 { "abc\\def" };
    string str2 { "abc/def" };
    Strings strings1 { "abc\\def", "ghi\\jkl" };
    Strings strings2 { "abc/def", "ghi/jkl" };
#elif _WIN32
    string str1 { "abc/def" };
    string str2 { "abc\\def" };
    Strings strings1 { "abc/def", "ghi/jkl" };
    Strings strings2 { "abc\\def", "ghi\\jkl" };
#else
    #error unknown OS
#endif

    // test fixing the path separator of a string
    EXPECT_EQ(fixPathSeparators(str1), str2);
    fixPathSeparators(&str1);   // modify the string
    EXPECT_EQ(str1, str2);

    // test fixing the path separator of a vector of strings
    EXPECT_EQ(fixPathSeparators(strings1), strings2);
    fixPathSeparators(&strings1);   // modify the strings
    EXPECT_EQ(strings1, strings2);
}
