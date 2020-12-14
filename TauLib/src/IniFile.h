#pragma once
#include <string>
#include <map>
#include <vector>
#include "TauLib.h"

///
/// @file
/// @brief Header file for Ini file routines.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///

struct IniFile {
    std::string iniFilePath;
    bool open {false};

    IniFile();
    IniFile(const std::string& _iniFilePath);

    bool Load(const std::string& _iniFilePath);
    bool Save();
    bool SaveAs(const std::string& _iniFilePath);
    void Clear();

    bool SectionExists(const std::string& sectionName);
    bool KeyExists(const std::string& sectionName, const std::string& key);
    std::string GetKey(const std::string& sectionName, const std::string& key);
    // if the key doesn't already exist, this will create it
    // if the sectionName doesn't already exist, this will create it
    void SetKey(const std::string& sectionName, const std::string& key, const std::string& value);
    bool DeleteKey(const std::string& sectionName, const std::string& key);

private:
    struct IniSection {
        IniSection(std::string _sectionName) : sectionName(_sectionName) { }

        std::string sectionName;   // section name example: [config] (but without the [])
        std::map<std::string, std::string> values;  // see example data above

        bool KeyExists(const std::string& key);
        std::string GetKey(const std::string& key);
        // if the key doesn't already exist, this will create it
        void SetKey(const std::string& key, const std::string& value);
        bool DeleteKey(const std::string& key);
    };
    std::vector<IniSection> iniSections;

    // returns end(iniSections) if not found
    std::vector<IniSection>::iterator FindSection(const std::string& sectionName);

    struct IniLine {
        std::string key;
        std::string whiteSpaceAfterKey;
        std::string whiteSpaceBeforeValue;
        int commentColum = 0;
        std::string comment;
    };

#ifdef _DEBUG
    void Dump();
#endif
};