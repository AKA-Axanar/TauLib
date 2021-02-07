#include "IniFileWithDefault.h"

using namespace std;
using namespace Tau;

///
/// @file
/// @brief CPP file for IniFileWithDefault.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///

//
// IniFileWithDefault::LoadDefaultIniFile
//
bool IniFileWithDefault::LoadDefaultIniFile(const std::string& _iniFilePath, bool _caseInsensitiveKeys)
    { return defaultIni.Load(_iniFilePath, _caseInsensitiveKeys); }

//
// IniFileWithDefault::SectionExists
//
bool IniFileWithDefault::SectionExists(const std::string& sectionName) const {
    if (IniFile::SectionExists(sectionName))
        return true;
    else
        return defaultIni.SectionExists(sectionName);
}

//
// IniFileWithDefault::KeyExists
//
bool IniFileWithDefault::KeyExists(const string& key, const string& sectionName) const {
    if (IniFile::KeyExists(key, sectionName))
        return true;
    else
        return defaultIni.KeyExists(key, sectionName);
}

//
// IniFileWithDefault::GetKeyValue
//
string IniFileWithDefault::GetKeyValue(const string& key, const string& sectionName) const {
    if (IniFile::KeyExists(key, sectionName))
        return IniFile::GetKeyValue(key, sectionName);
    else
        return defaultIni.GetKeyValue(key, sectionName);
}

//
// IniFileWithDefault::GetKeyValue_Int
//
int IniFileWithDefault::GetKeyValue_Int(const std::string& key, const std::string& sectionName) const {
    if (IniFile::KeyExists(key, sectionName))
        return IniFile::GetKeyValue_Int(key, sectionName);
    else
        return defaultIni.GetKeyValue_Int(key, sectionName);
}

//
// IniFileWithDefault::GetKeyValue_Ints
//
vector<int> IniFileWithDefault::GetKeyValue_Ints(const std::string& key, const std::string& sectionName) const {
    if (IniFile::KeyExists(key, sectionName))
        return IniFile::GetKeyValue_Ints(key, sectionName);
    else
        return defaultIni.GetKeyValue_Ints(key, sectionName);
}

//
// IniFileWithDefault::GetKeyValue_Float
//
float IniFileWithDefault::GetKeyValue_Float(const std::string& key, const std::string& sectionName) const {
    if (IniFile::KeyExists(key, sectionName))
        return IniFile::GetKeyValue_Float(key, sectionName);
    else
        return defaultIni.GetKeyValue_Float(key, sectionName);
}

//
// IniFileWithDefault::GetKeyValue_Floats
//
vector<float> IniFileWithDefault::GetKeyValue_Floats(const std::string& key, const std::string& sectionName) const {
    if (IniFile::KeyExists(key, sectionName))
        return IniFile::GetKeyValue_Floats(key, sectionName);
    else
        return defaultIni.GetKeyValue_Floats(key, sectionName);
}

//
// IniFileWithDefault::GetKeyValue_Double
//
double IniFileWithDefault::GetKeyValue_Double(const std::string& key, const std::string& sectionName) const {
    if (IniFile::KeyExists(key, sectionName))
        return IniFile::GetKeyValue_Double(key, sectionName);
    else
        return defaultIni.GetKeyValue_Double(key, sectionName);
}

//
// IniFileWithDefault::GetKeyValue_Doubles
//
vector<double> IniFileWithDefault::GetKeyValue_Doubles(const std::string& key, const std::string& sectionName) const {
    if (IniFile::KeyExists(key, sectionName))
        return IniFile::GetKeyValue_Doubles(key, sectionName);
    else
        return defaultIni.GetKeyValue_Doubles(key, sectionName);
}

