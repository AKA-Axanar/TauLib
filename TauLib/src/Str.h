#pragma once

#include <string>
#include <vector>

///
/// @file
/// @brief Header file for string routines.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

///
/// @brief namespace Tau - avoid conflict with other libraries
///
namespace Tau { // to avoid conflict with other libraries

                //*******************************
                // Strings (vector<string>)
                //*******************************
    
///
/// @brief Strings = vector<string>
///
using Strings = std::vector<std::string>;

///
/// @brief sortStrings - Sorts the passed vector of strings.
/// @param strings vector<string> to be sorted.
/// @return none.
///
void sortStrings(Strings& strings);

///
/// @brief sortStringsInsensitive - Does a case insensitive sort of the passed vector of strings.
/// @param strings vector<string> to be case insensitive sorted.
/// @return none.
///
void sortStringsInsensitive(Strings& strings);

                //*******************************
                // string trim
                //*******************************

///
/// @brief ltrim - trim the left leading whitespace from a string.
/// @param s string to trim (const& not modified).
/// @return The trimmed string.
///
std::string ltrim(const std::string& str);

///
/// @brief ltrim - trim the left leading whitespace from a string.
/// @param &string to trim (string is modified).
/// @return none
///
void ltrim(std::string* str);

///
/// @brief rtrim - trim the right leading whitespace from a string.
/// @param string to trim (const& not modified).
/// @return The trimmed string.
///
std::string rtrim(const std::string& s);

///
/// @brief rtrim - trim the right leading whitespace from a string.
/// @param &string to trim (string is modified).
/// @return none
///
void rtrim(std::string* s);

///
/// @brief trim - trim both the leading and trailing whitespace from a string.
/// @param string to trim (const& not modified).
/// @return The trimmed string.
///
std::string trim(const std::string& s);

///
/// @brief trim - trim both the leading and trailing whitespace from a string.
/// @param &string to trim (string is modified).
/// @return none
///
void trim(std::string* s);

                //*******************************
                // string case
                //*******************************

///
/// @brief lowerCase - Return the passed string as lower case.
/// @param string to convert to lower case.
/// @return The lower case string.
///
std::string lowerCase(const std::string& _s);

///
/// @brief lowerCase - Convert the passed satring to lower case.
/// @param &string to convert to lower case.
/// @return none
///
void lowerCase(std::string* s);

///
/// @brief upperCase - Return the passed string as upper case.
/// @param string to convert to upper case.
/// @return The upper case string.
///
std::string upperCase(const std::string& _s);

///
/// @brief upperCase - Convert the passed satring to upper case.
/// @param &string to convert to upper case.
/// @return none
///
void upperCase(std::string* s);

                //*******************************
                // string compare
                //*******************************

///
/// @brief icompareBool - Case insensitive string compare.
/// @param str_a Left hand string to compare.
/// @param str_b Right hand string to compare.
/// @return true if lower(str_a) == tolower(str_b)
///
bool icompareBool(const std::string& str_a, const std::string& str_b);

///
/// @brief icompareInt - Case insensitive string compare for sorting.
/// @param str_a Left hand string to compare.
/// @param str_b Right hand string to compare.
/// @return -1 if str_a < str_b, 0 if str_a == str_b, +1 if str_a > str_b
///
int icompareInt(const std::string& str_a, const std::string& bstr_b);

///
/// @brief sortStringCompare - Compare two strings (for lambdas).
///
bool sortStringCompare(const std::string& string1, const std::string& string2);

///
/// @brief sortStringCompare - Compare two strings (for lambdas).
///
bool sortStringCompareInsensitive(const std::string& string1, const std::string& string2);

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
std::string ReplaceSubStrings(const std::string& str, const std::string& fromSubStringOrLexicalExpression,
    const std::string& toSubString);

///
/// @brief ReplaceSubStrings - Replace all the matching substrings in a string.
/// @param str The &string to search.  The string is modified.
/// @param fromSubStringOrLexicalExpression The substring or lexical expression to match.
/// @param toSubString The substring to replace the substring with.
/// @return none
///
void ReplaceSubStrings(std::string* str, const std::string& fromSubStringOrLexicalExpression,
    const std::string& toSubString);

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
bool FoundLexExpr(const std::string& lexicalExpressionOrString, const std::string& str);

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
bool IsLexExpr(const std::string& lexicalExpressionOrString, const std::string& str);

///
/// @brief IsInt - Returns if the string is an integer.
///
bool IsInt(const std::string& str);

///
/// @brief IsFloat - Returns if the string is a float.
///
bool IsFloat(const std::string& str);

///
/// @brief FindLexExprMatches - returns all the matches of the lexical expression found in the string.
/// @param lexicalExpression The lexical expression to look for in the string.
/// @param str The string to search.
/// @remark FindLexExprMatches("[0-9]+", "abc 12, alpha 34 ,,5678XYZ");
/// @remark returns "12", "34", "5678"
/// @return vector<string> of results
///
Strings FindLexExprMatches(const std::string& lexicalExpression, const std::string& str);

///
/// @brief FindLexExprMatch - returns a match of the lexical expression if found in the string.
/// @param lexicalExpression The lexical expression to look for in the string.
/// @param str The string to search.
/// @return string of a match.  "" if none.
///
std::string FindLexExprMatch(const std::string& lexicalExpression, const std::string& str);

//*******************************
// split string
//*******************************

///
/// @brief SplitStringAtChars - returns the string pieces after splitting the string at the passed char or chars.
/// @param str The string to split.
/// @param splitAt The char or chars to split the string at.
/// @return vector<string> of results
///
Strings SplitStringAtChars(const std::string& str, const std::string& splitAt, bool trimTheWhitespaceFromThePieces);

///
/// @brief SplitStringAtCommas - returns the string pieces after splitting the string at the commas.
/// @param str The string to split.
/// @return vector<string> of results
///
Strings SplitStringAtCommas(const std::string& str, bool trimTheWhitespaceFromThePieces = true);

///
/// @brief CommaSepStringToInts - Takes a comma separated string of int's and returns a vector of int's.
/// @param str The string of comma separated int's.
/// @return vector<int> of the int's.
///
std::vector<int> CommaSepStringToInts(const std::string& str);

///
/// @brief CommaSepStringToFloats - Takes a comma separated string of floats and returns a vector of floats.
/// @param str The string of comma separated floats.
/// @return vector<int> of the floats.
///
std::vector<float> CommaSepStringToFloats(const std::string& str);

///
/// @brief CommaSepStringToDoubles - Takes a comma separated string of Doubles and returns a vector of Doubles.
/// @param str The string of comma separated Doubles.
/// @return vector<int> of the Doubles.
///
std::vector<double> CommaSepStringToDoubles(const std::string& str);

                //*******************************
                // string remove
                //*******************************

///
/// @brief RemoveCharFromString - removes all instances of a char from the string
/// @param str The string to search and modify
/// @param ch The char remove.
/// @return none
///
void RemoveCharFromString(std::string* str, char ch);

///
/// @brief RemoveCharFromString - removes all instances of a char from the string
/// @param str The string to search
/// @param ch The char remove.
/// @return The string with the chars removed
///
std::string RemoveCharFromString(const std::string& str, char ch);

///
/// @brief RemoveMultipleCharsFromString - removes all instances of multiple chars from the string
/// @param str The string to search and modify
/// @param charsToRemove The characters to be removed.
/// @return none
///
void RemoveMultipleCharsFromString(std::string* str, const std::string& charsToRemove);

///
/// @brief RemoveMultipleCharsFromString - removes all instances of multiple chars from the string
/// @param str The string to search
/// @param charsToRemove The characters to be removed.
/// @return The string with those characters removed.
///
std::string RemoveMultipleCharsFromString(const std::string& str, const std::string& charsToRemove);

///
/// @brief RemoveCRLFCharsFromEndOfString - removes any CR or LF chars from the end of the string.
/// @param str The string to search and modify
/// @return none
///
void RemoveCRLFCharsFromEndOfString(std::string* str);

///
/// @brief RemoveCRLFCharsFromEndOfString - removes any CR or LF chars from the end of the string.
/// @param str The string to search
/// @return The string with CR and LF's removed.
///
std::string RemoveCRLFCharsFromEndOfString(const std::string& str);

                //*******************************
                // string misc
                //*******************************

///
/// @brief Spaces(count)
/// @param count The number of spaces you want in the string
/// @return A string containing the desired number of spaces
///
inline std::string Spaces(size_t count) { return std::string(count, ' '); }

///
/// @brief DoubleQuoteStringIfSpace - if there is a space in the string, add a double quote to the front and back
/// 
std::string DoubleQuoteStringIfSpace(const std::string& s);

///
/// @brief DoubleQuoteStringIfSpace - if there is a space in the string, add a double quote to the front and back
/// 
void DoubleQuoteStringIfSpace(std::string* s);

} // end namespace Tau
