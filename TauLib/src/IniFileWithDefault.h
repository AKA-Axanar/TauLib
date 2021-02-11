#pragma once
#include "IniFile.h"

///
/// @file
/// @brief Header file for IniFileWithDefault.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///

                //*******************************
                // IniFileWithDefault
                //*******************************

///
/// @struct IniFileWithDefault is an IniFile with default key values in a default IniFile.
/// If a key doesn't exist in the IniFile it looks in the default IniFile.
/// 
/// @todo add quoted string support
/// 
struct IniFileWithDefault : public IniFile {
    IniFile defaultIni;                 ///< The default ini file.

    /// @brief Creates the base IniFile().
    IniFileWithDefault() : IniFile() {}

    /// @brief Creates the base IniFile().
    /// @param _iniFilePath The path of the ini file to load.
    IniFileWithDefault(const std::string& _iniFilePath, const std::string& _defaultSectionName = "") : IniFile(_iniFilePath, _defaultSectionName) {}

    /// @brief Creates the base IniFile and the default IniFile.
    /// @param _iniFilePath The path of the ini file to load.
    /// @param _defaltIniFilePath The path of the ini file to load.
    IniFileWithDefault(const std::string& _iniFilePath, const std::string& _defaltIniFilePath, const std::string& _defaultSectionName = "") : IniFile(_iniFilePath, _defaultSectionName) 
        { LoadDefaultIniFile(_defaltIniFilePath, _defaultSectionName); }

    /// @brief Creates the base IniFile and the default IniFile.
    /// @param _iniFilePath The path of the ini file to load.
    /// @param _defaltIniFilePath The path of the ini file to load.
    bool LoadWithDefault(const std::string& _iniFilePath, const std::string& _defaltIniFilePath, const std::string& _defaultSectionName = "") {
        bool ok = IniFile::Load(_iniFilePath, _defaultSectionName) ;
        if (!ok)
            return false;
        ok = LoadDefaultIniFile(_defaltIniFilePath, _defaultSectionName);
        return ok;
        }

private:
    /// @brief Loads the default IniFile
    bool LoadDefaultIniFile(const std::string& _iniFilePath, const std::string& _defaultSectionName = "");

public:
    /// @brief If the section doesn't exist try the default ini file
    bool SectionExists(const std::string& sectionName) const;

    /// @brief If the key doesn't exist try the default ini file
    bool KeyExists(const std::string& key, const std::string& sectionName) const;
    bool KeyExists(const std::string& key) const { return KeyExists(key, defaultSectionName); }

    /// @brief If the key value doesn't exist try the default ini file
    std::string GetKeyValue(const std::string& key, const std::string& sectionName) const;
    std::string GetKeyValue(const std::string& key) const { return GetKeyValue(key, defaultSectionName); }

    /// @brief Returns a key value for a passed key and section name
    /// @param key - the key to search for
    /// @param sectionName - the section name the key is in, if any
    /// @return Returns the value of the key/value pair converted to an integer.
    int GetKeyValue_Int(const std::string& key, const std::string& sectionName) const;
    int GetKeyValue_Int(const std::string& key) const { return GetKeyValue_Int(key, defaultSectionName); }
    std::vector<int> GetKeyValue_Ints(const std::string& key, const std::string& sectionName) const;
    std::vector<int> GetKeyValue_Ints(const std::string& key) const { return GetKeyValue_Ints(key, defaultSectionName); }

    /// @brief Returns a key value for a passed key and section name
    /// @param key - the key to search for
    /// @param sectionName - the section name the key is in, if any
    /// @return Returns the value of the key/value pair converted to a float.
    float GetKeyValue_Float(const std::string& key, const std::string& sectionName) const;
    float GetKeyValue_Float(const std::string& key) const { return GetKeyValue_Float(key, defaultSectionName); }
    std::vector<float> GetKeyValue_Floats(const std::string& key, const std::string& sectionName) const;
    std::vector<float> GetKeyValue_Floats(const std::string& key) const { return GetKeyValue_Floats(key, defaultSectionName); }

    /// @brief Returns a key value for a passed key and section name
    /// @param key - the key to search for
    /// @param sectionName - the section name the key is in, if any
    /// @return Returns the value of the key/value pair converted to a double.
    double GetKeyValue_Double(const std::string& key, const std::string& sectionName) const;
    double GetKeyValue_Double(const std::string& key) const { return GetKeyValue_Double(key, defaultSectionName); }
    std::vector<double> GetKeyValue_Doubles(const std::string& key, const std::string& sectionName) const;
    std::vector<double> GetKeyValue_Doubles(const std::string& key) const { return GetKeyValue_Doubles(key,defaultSectionName); }
};