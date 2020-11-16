#include "pch.h"
#include "Str.h"

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
    EXPECT_EQ(ReplaceSubStrings("abcdefabcdef", "abc", "XXX"), "XXXdefXXXdef");
    string temp = "abcdefabcdef";
    ReplaceSubStrings(&temp, "abc", "XXX");
    EXPECT_EQ(temp, "XXXdefXXXdef");

    EXPECT_EQ(FoundLexExpr("[a-z]+", "abcdefabcdef"), true);
    EXPECT_EQ(FoundLexExpr("[0-9]+", "abcdefabcdef"), false);
    EXPECT_EQ(FoundLexExpr("def", "abcdefabcdef"), true);

}

