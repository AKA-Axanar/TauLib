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
/// @todo add quoted string support?
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

private:
    struct IniSection;
    std::vector<IniSection> iniSections;

    // returns end(iniSections) if not found
    std::vector<IniSection>::iterator FindSectionName(const std::string& sectionName);

                //*******************************
                // IniFile::IniLineInfo
                //*******************************

    struct IniLineInfo {
        IniLineInfo(const std::string& line)
            { scanLine(line); }

        void scanLine(const std::string& line);
        std::string rebuildLine() const;

        void padToCommentColumn(std::string* line, int column) const;
        std::string GetAndRemoveLeadingWhitespace(std::string* line) const;

        // scan result
        std::string sectionDefine;  // if it's a section (example: "[config]") it's the only thing on the line
        std::string key;
        std::string whiteSpaceAfterKey;
        std::string whiteSpaceBeforeValue;
        std::string value;
        int commentColumn = 0;      // index starts at 0
        std::string comment;
    };

                //*******************************
                // IniFile::IniSection
                //*******************************

    struct IniSection {
        IniSection(const std::string& _sectionLine) : sectionLine(_sectionLine) { 
            sectionName = sectionLine.sectionDefine;
         }

        std::string sectionName;    // section name example: for "[config]" the sectionName == "config"
        // the info from the scanned sectionName line.  
        // if sectionDefine is "" this line does not get written to the ini file.
        IniLineInfo sectionLine;    

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