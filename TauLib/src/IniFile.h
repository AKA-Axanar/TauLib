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
/// @brief IniFile reads an ini file into a map of key/value pairs with section names [config], [info], [settings], etc.
/// Keys can be modified, added, or deleted and saved in the original ini file or written to a new file.
/// A semicolon to the end of the line is a comment.
/// When you save a modified ini file the comments are restored to the original key/value pair.
///
/// @todo add quoted string support
/// @todo handle escape char.  \#, \;, \\.  output \ during save.
/// @todo unit tests
/// 
struct IniFile {
    std::string iniFilePath;
    bool open {false};

    IniFile();
    IniFile(const std::string& _iniFilePath);

    bool Load(const std::string& _iniFilePath);
    bool Save();
    bool SaveAs(const std::string& filePath);
    void Clear();

    bool SectionExists(const std::string& sectionName);
    bool KeyExists(const std::string& key, const std::string& sectionName="");
    std::string GetKeyValue(const std::string& key, const std::string& sectionName="");

    // if the key doesn't already exist, it's created
    // if the sectionName doesn't already exist, it's created
    void SetKeyValue(const std::string& key, const std::string& value, const std::string& sectionName="");
    bool DeleteKey(const std::string& key, const std::string& sectionName="");

    friend std::ostream& operator << (std::ostream& os, const IniFile& iniFile);

    ///
    /// @brief Fix any / or \ path separators to be correct for the OS.
    /// @param iniFilePath - the path of the ini file
    /// @return true if any key was changed and the ini file rewritten
    /// 
    static bool FixPathSeparators(const std::string& iniFilePath);

private:
    struct IniSection;
    std::vector<IniSection> iniSections;

    // returns end(iniSections) if not found
    std::vector<IniSection>::iterator FindSectionName(const std::string& sectionName);

                //*******************************
                // IniFile::IniLineInfo
                //*******************************

    struct IniLineInfo {
        IniLineInfo() { }

        IniLineInfo(const std::string& line)
            { scanLine(line); }

        bool scanLine(const std::string& line);
        std::string rebuildLine() const;

        void padToCommentColumn(std::string* line, int column) const;
        std::string GetAndRemoveLeadingWhitespace(std::string* line) const;

        // scan result
        std::string leadingWhiteSpace;

        // section name
        bool lineContainsASectionDefine = false;    // this bool exists because there is a dummy define of "" at the top
        std::string section;                        // if it's a section (example: "[config]")
        std::string whiteSpaceAfterSection;

        // key = value
        std::string key;
        std::string whiteSpaceAfterKey;
        std::string whiteSpaceBeforeValue;
        std::string value;
        std::string whiteSpaceAfterValue;

        std::string comment;
    };

                //*******************************
                // IniFile::IniSection
                //*******************************

    struct IniSection {
        IniSection(const std::string& line);

        std::string sectionName;    // section name example: for "[config]" the sectionName == "config"
        // the info from the scanned sectionName line.  
        // if sectionDefine is "" this line does not get written to the ini file.
        IniLineInfo sectionLine;    // the line defining the section name which may or may not have a comment

        std::vector<IniLineInfo> iniLineInfos;
        std::map<std::string, std::string> values;  // see example data above

        bool KeyExists(const std::string& key);
        
        std::string GetKey(const std::string& key);
        // if the key doesn't already exist, this will create it
        void SetKey(const std::string& key, const std::string& value);
        bool DeleteKey(const std::string& key);

        // returns end(iniLineInfos) if not found
        std::vector<IniLineInfo>::iterator FindKeyLine(const std::string& key);
    };
};