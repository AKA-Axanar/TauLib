#pragma once

/**
 * @file
 *
 * Header file for string routines.
 *
 */

#include <string>
#include <vector>

/**
 * \brief avoid conflict with other libraries
 */
namespace Tau { // to avoid conflict with other libraries

                //*******************************
                // Strings
                //*******************************
    
/**
 * \brief vector<string>
 */
using Strings = std::vector<std::string>;

/**
 * \brief Sorts the passed vector of strings.
 *
 * \param strings vector<string> to be sorted.
 *
 * \return none.
 */
void sortStrings(Strings& strings);

/**
 * \brief Does a case insensitive sort of the passed vector of strings.
 *
 * \param strings vector<string> to be case insensitive sorted.
 *
 * \return none.
 */
void sortStringsInsensitive(Strings& strings);

                //*******************************
                // string trim
                //*******************************

/**
 * \brief trim the left leading whitespace from a string.
 *
 * \param string to trim (const& not modified).
 *
 * \return The trimmed string.
 */
std::string ltrim(const std::string& str);

/**
 * \brief trim the left leading whitespace from a string.
 *
 * \param &string to trim (string is modified).
 *
 * \return none
 */
void ltrim(std::string* str);

/**
 * \brief trim the right leading whitespace from a string.
 *
 * \param string to trim (const& not modified).
 *
 * \return The trimmed string.
 */
std::string rtrim(const std::string& s);

/**
 * \brief trim the right leading whitespace from a string.
 *
 * \param &string to trim (string is modified).
 *
 * \return none
 */
void rtrim(std::string* s);

/**
 * \brief trim both the leading and trailing whitespace from a string.
 *
 * \param string to trim (const& not modified).
 *
 * \return The trimmed string.
 */
std::string trim(const std::string& s);

/**
 * \brief trim both the leading and trailing whitespace from a string.
 *
 * \param &string to trim (string is modified).
 *
 * \return none
 */
void trim(std::string* s);

                //*******************************
                // string case
                //*******************************

/**
 * \brief Return the passed string as lower case.
 *
 * \param string to convert to lower case.
 *
 * \return The lower case string.
 */
std::string lowerCase(const std::string& _s);

/**
 * \brief Convert the passed satring to lower case.
 *
 * \param &string to convert to lower case.
 *
 * \return none
 */
void lowerCase(std::string* s);

/**
 * \brief Return the passed string as upper case.
 *
 * \param string to convert to upper case.
 *
 * \return The upper case string.
 */
std::string upperCase(const std::string& _s);

/**
 * \brief Convert the passed satring to upper case.
 *
 * \param &string to convert to upper case.
 *
 * \return none
 */
void upperCase(std::string* s);

                //*******************************
                // string compare
                //*******************************

/**
 * \brief Case insensitive string compare.
 *
 * \param str_a Left hand string to compare.
 * \param str_b Right hand string to compare.
 *
 * \return true if lower(str_a) == tolower(str_b)
 */
bool icompareBool(const std::string& str_a, const std::string& str_b);

/**
 * \brief Case insensitive string compare for sorting.
 *
 * \param str_a Left hand string to compare.
 * \param str_b Right hand string to compare.
 *
 * \return -1 if str_a < str_b, 0 if str_a == str_b, +1 if str_a > str_b
 */
int icompareInt(const std::string& str_a, const std::string& bstr_b);

                //*******************************
                // string replace
                //*******************************

/**
 * \brief Replace all the matching substrings in a string.
 *
 * \param str The string to search.
 * \param fromSubStringOrLexicalExpression The substring or lexical expression to match.
 * \param toSubString The substring to replace the substring with.
 *
 * \return The resulting string.
 */
std::string ReplaceSubStrings(const std::string& str, const std::string& fromSubStringOrLexicalExpression,
    const std::string& toSubString);

/**
 * \brief Replace all the matching substrings in a string.
 *
 * \param str The &string to search.  The string is modified.
 * \param fromSubStringOrLexicalExpression The substring or lexical expression to match.
 * \param toSubString The substring to replace the substring with.
 *
 * \return none
 */
void ReplaceSubStrings(std::string* str, const std::string& fromSubStringOrLexicalExpression,
    const std::string& toSubString);

                //*******************************
                // string find
                //*******************************


/**
 * \brief returns whether the lexical expression (or plain string) is found in a string.
 *
 * \param lexicalExpressionOrString The string or lexical expression to look for in the string.
 * \param str The string to search.
 *
 * \remark lexical expression = "[A-Za-z0-9]+"
 * \remark lexical expression = "FindMe"
 *
 * \return true or false
 */
bool FoundLexExpr(const std::string& lexicalExpressionOrString, const std::string str);


/**
 * \brief returns all the matches of the lexical expression found in the string.
 *
 * \param lexicalExpression The lexical expression to look for in the string.
 * \param str The string to search.
 *
 * \remark FindLexExprMatches("[0-9]+", "abc 12, alpha 34 ,,5678XYZ");
 * \remark returns "12", "34", "5678"
 *
 * \return vector<string> of results
 */
std::vector<std::string> FindLexExprMatches(const std::string& lexicalExpression, const std::string str);

} // end namespace Tau
