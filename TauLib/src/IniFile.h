#pragma once
#include <string>
#include <map>
#include <vector>
#include <ostream>
#include "TauLib.h"

///
/// @file
/// @brief Header file for Ini file routines.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///

                //*******************************
                // IniFile
                //*******************************

///
/// @struct IniFile reads an ini file into a map of key/value pairs with section names [config], [info], [settings], etc.
/// Keys can be modified, added, or deleted and saved in the original ini file or written to a new file.
/// A semicolon is a comment to the end of the line.
/// When you save a modified ini file the comments are restored.
/// @note Avoid using tabs as comments might not be restored to the file in the original column position if the key value is changed.
/// The ini file can have zero, one, or more than one, section names enclosed in [ ].  Section declarations are on their own line.
/// Passing a section name of "" to a routine means the key is not within a section.  The last argument to a key get/set/query ruotine
/// defaults to "" which means the key is not insde a section area.
/// 
/// @todo add quoted string support
/// 
struct IniFile {
    std::string iniFilePath;            ///< The file path of the opened ini file.  Used by Save().
    bool open {false};                  ///< true if an ini file has been opened and parsed.
    bool caseInsensitiveKeys {true};    ///< if true, keys (and section names) are case insensitive.
    std::string defaultSectionName;

    /// @brief IniFile ctor.  
    /// Creates an empty IniFile.  Also adds the dummy [] section name where key that aren't inside a section name are added.
    IniFile();

    /// @brief Calls IniFile().  Then loads the passed ini file.
    /// @param _iniFilePath The path of the ini file to load.
    IniFile(const std::string& _iniFilePath, const std::string& _defaultSectionName = "");

    /// @brief Loads the passed ini file, scans the lines in the ini file saving the parsed pieces, and builds a map of the key/value pairs.
    /// @param _iniFilePath The path of the ini file to load.
    bool Load(const std::string& _iniFilePath, const std::string& _defaultSectionName = "");

    /// @brief Save the ini key/value pairs, section names, and comments back to original opened ini file.
    /// @return true if data successfully save back to the file.
    bool Save() const;

    /// @brief Save the ini key/value pairs, section names, and comments to passed filename.
    /// @param filePath - The path of the file to save the save.
    /// @return true if data successfully save back to the file.
    bool SaveAs(const std::string& filePath) const;

    /// @brief Clears the data.  Keeps the filename if any.
    /// @return none
    void Clear();

    /// @brief tests if a sction name exists in the data
    /// @param sectionName - the [sectionName] to look for.
    /// @return Returns true if the section name exists
    bool SectionExists(const std::string& sectionName) const;

    /// @brief Tests if the key exists
    /// @param key - the key to search for
    /// @param sectionName - the section name the key is in, if any
    /// @return Returns true if the key exists in the section
    bool KeyExists(const std::string& key, const std::string& sectionName) const;
    bool KeyExists(const std::string& key) const { return KeyExists(key, defaultSectionName); }

    /// @brief Returns a key value for a passed key and section name
    /// @param key - the key to search for
    /// @param sectionName - the section name the key is in, if any
    /// @return Returns the string value of the key/value pair.
    std::string GetKeyValue(const std::string& key, const std::string& sectionName) const;
    std::string GetKeyValue(const std::string& key) const { return GetKeyValue(key, defaultSectionName); }

    /// @brief Returns a key value for a passed key and section name
    /// @param key - the key to search for
    /// @param sectionName - the section name the key is in, if any
    /// @return Returns the value of the key/value pair converted to an integer.
    int GetKeyValue_Int(const std::string& key, const std::string& sectionName) const;
    std::vector<int> GetKeyValue_Ints(const std::string& key, const std::string& sectionName) const;
    int GetKeyValue_Int(const std::string& key) const { return GetKeyValue_Int(key, defaultSectionName); }
    std::vector<int> GetKeyValue_Ints(const std::string& key) const { return GetKeyValue_Ints(key, defaultSectionName); }

    /// @brief Returns a key value for a passed key and section name
    /// @param key - the key to search for
    /// @param sectionName - the section name the key is in, if any
    /// @return Returns the value of the key/value pair converted to a float.
    float GetKeyValue_Float(const std::string& key, const std::string& sectionName) const;
    std::vector<float> GetKeyValue_Floats(const std::string& key, const std::string& sectionName) const;
    float GetKeyValue_Float(const std::string& key) const { return GetKeyValue_Float(key, defaultSectionName); }
    std::vector<float> GetKeyValue_Floats(const std::string& key) const { GetKeyValue_Floats(key, defaultSectionName); }

    /// @brief Returns a key value for a passed key and section name
    /// @param key - the key to search for
    /// @param sectionName - the section name the key is in, if any
    /// @return Returns the value of the key/value pair converted to a double.
    double GetKeyValue_Double(const std::string& key, const std::string& sectionName) const;
    std::vector<double> GetKeyValue_Doubles(const std::string& key, const std::string& sectionName) const;
    double GetKeyValue_Double(const std::string& key) const { return GetKeyValue_Double(key, defaultSectionName); }
    std::vector<double> GetKeyValue_Doubles(const std::string& key) const { return GetKeyValue_Doubles(key, defaultSectionName); }

    /// @brief Sets a key value of a passed key and section name
    /// @param key - the key to search for
    /// @param value - the value to set
    /// @param sectionName - the section name the key is in, if any
    /// @return none
    /// @note if the key doesn't already exist, it's created
    /// @note if the sectionName doesn't already exist, it's created
    void SetKeyValue(const std::string& key, const std::string& value, const std::string& sectionName);
    void SetKeyValue(const std::string& key, const std::string& value) { return SetKeyValue(key, value, defaultSectionName); }

    /// @brief Sets a key value to an int
    /// @param key - the key to search for
    /// @param value - the integer value to set
    /// @param sectionName - the section name the key is in, if any
    /// @return none
    /// @note if the key doesn't already exist, it's created
    /// @note if the sectionName doesn't already exist, it's created
    void SetKeyValue_Int(const std::string& key, int value, const std::string& sectionName);
    void SetKeyValue_Int(const std::string& key, int value) { return SetKeyValue_Int(key, value, defaultSectionName); }

    /// @brief Sets a key value to the comma delimited string of a series of int's
    /// @param key - the key to search for
    /// @param value - a vector of int's to set the comma delimited string to
    /// @param sectionName - the section name the key is in, if any
    /// @return none
    /// @note if the key doesn't already exist, it's created
    /// @note if the sectionName doesn't already exist, it's created
    void SetKeyValue_Ints(const std::string& key, std::vector<int> values, const std::string& sectionName);
    void SetKeyValue_Ints(const std::string& key, std::vector<int> values) { return SetKeyValue_Ints(key, values, defaultSectionName); }

    /// @brief Sets a key value to a float
    /// @param key - the key to search for
    /// @param value - the float value to set
    /// @param sectionName - the section name the key is in, if any
    /// @return none
    /// @note if the key doesn't already exist, it's created
    /// @note if the sectionName doesn't already exist, it's created
    void SetKeyValue_Float(const std::string& key, float value, const std::string& sectionName);
    void SetKeyValue_Float(const std::string& key, float value) { return SetKeyValue_Float(key, value, defaultSectionName); }

    /// @brief Sets a key value to the comma delimited string of a series of floats
    /// @param key - the key to search for
    /// @param value - a vector of floats to set the comma delimited string to
    /// @param sectionName - the section name the key is in, if any
    /// @return none
    /// @note if the key doesn't already exist, it's created
    /// @note if the sectionName doesn't already exist, it's created
    void SetKeyValue_Floats(const std::string& key, std::vector<float> values, const std::string& sectionName);
    void SetKeyValue_Floats(const std::string& key, std::vector<float> values) { return SetKeyValue_Floats(key, values, defaultSectionName); }

    /// @brief Sets a key value to a double
    /// @param key - the key to search for
    /// @param value - the double value to set
    /// @param sectionName - the section name the key is in, if any
    /// @return none
    /// @note if the key doesn't already exist, it's created
    /// @note if the sectionName doesn't already exist, it's created
    void SetKeyValue_Double(const std::string& key, double value, const std::string& sectionName);
    void SetKeyValue_Double(const std::string& key, double value) { return SetKeyValue_Double(key, value, defaultSectionName); }

    /// @brief Sets a key value to the comma delimited string of a series of doubles
    /// @param key - the key to search for
    /// @param value - a vector of doubles to set the comma delimited string to
    /// @param sectionName - the section name the key is in, if any
    /// @return none
    /// @note if the key doesn't already exist, it's created
    /// @note if the sectionName doesn't already exist, it's created
    void SetKeyValue_Doubles(const std::string& key, std::vector<double> values, const std::string& sectionName);
    void SetKeyValue_Doubles(const std::string& key, std::vector<double> values) { return SetKeyValue_Doubles(key, values, defaultSectionName); }

    /// @brief Deletes a key value for a passed key and section name
    /// @param key - the key to delete
    /// @param sectionName - the section name the key is in, if any
    /// @return Returns true if the key was successfully found and deleted.
    bool DeleteKey(const std::string& key, const std::string& sectionName);
    bool DeleteKey(const std::string& key) { return DeleteKey(key,defaultSectionName); }

    /// @brief Writes the entire ini data to a ostream.
    /// You could output to cout or to an ofstream file stream
    friend std::ostream& operator << (std::ostream& os, const IniFile& iniFile);

    /// @brief Fix any / or \ path separators to be correct for the OS.
    /// @param iniFilePath - the path of the ini file
    /// @return true if any key was changed and the ini file rewritten
    static bool FixPathSeparators(const std::string& iniFilePath);

    //
    // Get list of section names and key names
    //

    /// @brief Return the list of section names.
    std::vector<std::string> GetSectionNames() const;
 
    /// @brief Return the list of keys in a section.
    std::vector<std::string> GetKeyNamesInSection(const std::string& sectionName) const;
 
    /// @brief Return the list of keys in a section.
    std::map<std::string, std::string> GetKeyPairsInSection(const std::string& sectionName) const;
 
    /// @brief Return all the keys.
    /// @return A vector of tuples of <string, string, string> = <section, key, value>
    std::vector<std::tuple<std::string, std::string, std::string>> GetAllKeyPairs() const;
 
private:
    /// @brief Compares two key strings depending on the caseInsensitiveKeys flag.
    /// @return true if the two key strings are "equal" depending on the caseInsensitiveKeys flag.<returns></returns>
    bool CompareKeys(const std::string& key1, const std::string& key2) const;

    /// @brief Returns the passed key as lowercase if caseInsensitiveKeys is true
    std::string AdjustKeyCase(const std::string& key) const;

    struct IniSection;
    std::vector<IniSection> iniSections;    ///< vector of IniSection's.  Each section conatins the map of key/value's and the parsed line info from the file

    /// @brief Finds a section for a section name in iniSections.
    /// @param sectionName The secontion to search for.
    /// @return An iterator to the section in the vector or end(iniSections) if not found
    std::vector<IniSection>::iterator FindSectionName(const std::string& sectionName);
    std::vector<IniSection>::const_iterator FindSectionName(const std::string& sectionName) const;

                //*******************************
                // IniFile::IniLine
                //*******************************

    /// @struct IniLine The parsed info from an ini file line.
    struct IniLine {

        /// @brief creates an empty IniLine with all default values
        IniLine() { }

        /// @brief IniLine Ctor that parses the passed ini file string into its components
        /// @param line the string (from an ini file) to parse
        IniLine(const std::string& line)
            { ParseLine(line); }

        /// @brief Parses the passed ini file string into its components
        /// @param line the string (from an ini file) to parse
        /// @return true if successfully parsed
        bool ParseLine(const std::string& line);
        std::string RebuildLine() const;

        /// @brief Removes any leading whitespace from the passed string
        /// @parem the string to modify
        /// @return the whirespace that was removed fromt he string
        std::string GetAndRemoveLeadingWhitespace(std::string* line) const;

        //
        // Parsed pieces and info.
        //

        std::string leadingWhiteSpace;  ///< whitespace before the key or section or comment (if the line contains only a comment)

        // section name
        bool lineContainsASectionDefine = false;    ///< this bool exists because there is a dummy define of "" at the top
        std::string section;                        ///< section name if the line declares a section (example: "[config]")
        std::string whiteSpaceAfterSection;         ///< whitespace after a section declaration

        // key = value
        std::string key;                            ///< the key
        std::string whiteSpaceAfterKey;             ///< the whitespace between a key and the =
        std::string whiteSpaceBeforeValue;          ///< the whitespace between the = and the value
        std::string value;                          ///< the key value
        std::string whiteSpaceAfterValue;           ///< the whitespace between the value and any comment

        std::string comment;                        ///< the comment, if any
    };

                //*******************************
                // IniFile::IniSection
                //*******************************

    /// @struct IniSection An ini file section
    struct IniSection {
        IniSection(IniFile* _iniFile, const std::string& line);

        IniFile* iniFile;
        std::string sectionName;    ///< section name. example: for "[config]" the sectionName == "config"
        IniLine sectionLine;        ///< The parsed info from the line containing the section name declaration.
                                    ///< if section name is "" this line does not get written to the ini file.

        std::vector<IniLine> iniLines;  ///< The parsed ini file lines for key/value pairs and comment lines.
                                        ///< Section declarations are not in this vector.  A section name would create a new IniSection.

        std::map<std::string, std::string> values;  ///< The map of key/value pairs

        /// @brief Test if a key exists
        /// @param key The key to test for existence.
        /// @return true if the key exists.
        bool KeyExists(const std::string& key) const;
        
        /// @brief Get the value of a key.
        /// @param key The key to get the value of.
        /// @return the key's value string.  Returns "" if the key does not exist.
        std::string GetKey(const std::string& key) const;

        /// @brief Set a key's value string.
        /// @param key The key to set.
        /// @param value The value for the key.
        /// @return none
        void SetKeyValue(const std::string& key, const std::string& value);

        /// @brief Detelte a key.
        /// @param key The key to delete.
        /// @return true if successful
        bool DeleteKey(const std::string& key);

        /// @brief Find the IniLine for a key.
        /// @param key The key to find.
        /// @return An iterator to the IniLine for the key.  Returns end(iniLines) if the key isn't found.
        std::vector<IniLine>::iterator FindKeyLine(const std::string& key);
        std::vector<IniLine>::const_iterator FindKeyLine(const std::string& key) const;
    };
};

using CfgFile = IniFile;
