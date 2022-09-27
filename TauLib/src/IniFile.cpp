#include "IniFile.h"
#include <regex>
#include "Str.h"
#include "Sep.h"
#include "DirFile.h"
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ranges>

using namespace std;
using namespace Tau;

///
/// @file
/// @brief CPP file for Ini file routines.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///

                //*******************************
                // IniFile
                //*******************************

//
// IniFile::IniFile
//
IniFile::IniFile() {
    // add a dummy "" section for keys that aren't inside a section.  the saved "[]" is not written to the file.  
    // any keys not in a section are written to the top of the file with no section name above them.
    iniSections.emplace_back(this, "");
}

//
// IniFile::IniFile
//
IniFile::IniFile(const string& _iniFilePath, const std::string& _defaultSectionName) : IniFile() {
    Load(_iniFilePath, _defaultSectionName);
}

//
// bool IniFile::Load
//
bool IniFile::Load(const string& _iniFilePath, const std::string& _defaultSectionName) {
    Clear();
    bool success = false;
    iniFilePath = _iniFilePath;
    defaultSectionName = _defaultSectionName;

    Strings fileLines = ReadTextFileAsAStringArray(iniFilePath, /*removeCRLF*/ true);

    for (const auto& fileLine : fileLines) {
        IniLine iniLine(fileLine);      // scan the line for a section name, key, value, and comment

        if (!iniLine.section.empty()) {
            // the line is a [section]. add the section name to the section list
            if (!SectionExists(iniLine.section))
                iniSections.emplace_back(this, fileLine);
        } else {
            // sectionname "" is not in the list and we are about to add a key to the "" section, add the "" section line
            if (iniSections.size() == 0)
                iniSections.emplace_back(this, "");

            // if the line has a key definition, add it to the map of key/value pairs
            if (!iniLine.key.empty())
                iniSections.back().values[AdjustKeyCase(iniLine.key)] = iniLine.value;

            // add the line info to the list of lines and map of keys in the current/last section
            iniSections.back().iniLines.emplace_back(iniLine);
        }
    }
    success = true;

    return success;
}

//
// IniFile::Save
//
bool IniFile::Save() const {
    if (iniFilePath == "")
        return false;

    return SaveAs(iniFilePath);
}

//
// IniFile::SaveAs
//
bool IniFile::SaveAs(const string& filePath) const {
    ofstream ofile(filePath.c_str(), ofstream::out | ofstream::trunc);
    if (!ofile.is_open())
        return false;

    ofile << *this;
    ofile.close();

    return true;
}

//
// IniFile::Clear
// Clears the data.  Keeps the filename if any.
//
void IniFile::Clear() {
    iniSections.clear();
}

//
// IniFile::SectionExists
//
bool IniFile::SectionExists(const std::string& sectionName) const {
    return FindSectionName(sectionName) != end(iniSections);
}

//
// IniFile::KeyExists
//
bool IniFile::KeyExists(const string& key, const string& sectionName) const {
    if (SectionExists(sectionName))
        return FindSectionName(sectionName)->KeyExists(key);
    else
        return false;
}

//
// IniFile::GetKeyValue
//
string IniFile::GetKeyValue(const string& key, const string& sectionName) const {
    if (SectionExists(sectionName))
        return FindSectionName(sectionName)->GetKeyValue(key);
    else
        return "";
}

//
// IniFile::GetKeyValue_Int
//
int IniFile::GetKeyValue_Int(const std::string& key, const std::string& sectionName) const {
    string value = GetKeyValue(key, sectionName);
    if (IsInt(value))
        return stoi(value);
    else {
        cerr << "value of ini key '" << key << "' is not an integer" << endl;
        return 0;
    }
}

//
// IniFile::GetKeyValue_Ints
//
vector<int> IniFile::GetKeyValue_Ints(const std::string& key, const std::string& sectionName) const {
    return CommaSepStringToInts(GetKeyValue(key, sectionName));
}

//
// IniFile::GetKeyValue_Int64
//
int64_t IniFile::GetKeyValue_Int64(const std::string& key, const std::string& sectionName) const {
    string value = GetKeyValue(key, sectionName);
    if (IsInt(value)) {
        istringstream iss(value);
        int64_t i64value;
        iss >> i64value;
        return i64value;
    }
    else {
        cerr << "value of ini key '" << key << "' is not an integer" << endl;
        return 0;
    }
}

//
// IniFile::GetKeyValue_Bool
//
bool IniFile::GetKeyValue_Bool(const std::string& key, bool defaultValue, const std::string& sectionName) const {
    string value = GetKeyValue(key, sectionName);
    if (icompareBool(value, "true"))
        return true;
    else if (icompareBool(value, "false"))
        return false;
    else
        return defaultValue;
}

//
// IniFile::GetKeyValue_Float
//
float IniFile::GetKeyValue_Float(const std::string& key, const std::string& sectionName) const {
    string value = GetKeyValue(key, sectionName);
    if (IsFloat(value))
        return stof(value);
    else {
        cerr << "value of ini key '" << key << "' is not a float" << endl;
        return 0.0;
    }
}

//
// IniFile::GetKeyValue_Floats
//
vector<float> IniFile::GetKeyValue_Floats(const std::string& key, const std::string& sectionName) const {
    return CommaSepStringToFloats(GetKeyValue(key, sectionName));
}

//
// IniFile::GetKeyValue_Double
//
double IniFile::GetKeyValue_Double(const std::string& key, const std::string& sectionName) const {
    string value = GetKeyValue(key, sectionName);
    if (IsFloat(value))
        return stod(value);
    else {
        cerr << "value of ini key '" << key << "' is not a double" << endl;
        return 0.0;
    }
}

//
// IniFile::GetKeyValue_Doubles
//
vector<double> IniFile::GetKeyValue_Doubles(const std::string& key, const std::string& sectionName) const {
    return CommaSepStringToDoubles(GetKeyValue(key, sectionName));
}

//
// IniFile::SetKeyValue
//
// if the key doesn't already exist, this will create it
// if the sectionName doesn't already exist, this will create it
void IniFile::SetKeyValue(const string& key, const string& value, const string& sectionName) {
    if (!SectionExists(sectionName))
        iniSections.emplace_back(this, string("[") + sectionName + "]");

    FindSectionName(sectionName)->SetKeyValue(key, value);
}

//
// IniFile::SetKeyValue_Int
//
void IniFile::SetKeyValue_Int(const std::string& key, int value, const std::string& sectionName) {
    string s = to_string(value);
    SetKeyValue(key, s, sectionName);
}

//
// IniFile::SetKeyValue_Ints
//
void IniFile::SetKeyValue_Ints(const std::string& key, std::vector<int> values, const std::string& sectionName) {
    if (values.size() > 0) {
        string s;
        for (int i = 0; i < values.size(); ++i) {
            s += to_string(values[i]);
            if (i < values.size() - 1)
                s += ",";
        }
        SetKeyValue(key, s, sectionName);
    }
}

//
// IniFile::SetKeyValue_Float
//
void IniFile::SetKeyValue_Float(const std::string& key, float value, const std::string& sectionName) {
    string s = to_string(value);
    SetKeyValue(key, s, sectionName);
}

//
// IniFile::SetKeyValue_Floats
//
void IniFile::SetKeyValue_Floats(const std::string& key, std::vector<float> values, const std::string& sectionName) {
    if (values.size() > 0) {
        string s;
        for (int i = 0; i < values.size(); ++i) {
            s += to_string(values[i]);
            if (i < values.size() - 1)
                s += ",";
        }
        SetKeyValue(key, s, sectionName);
    }
}

//
// IniFile::SetKeyValue_Double
//
void IniFile::SetKeyValue_Double(const std::string& key, double value, const std::string& sectionName) {
    string s = to_string(value);
    SetKeyValue(key, s, sectionName);
}

//
// IniFile::SetKeyValue_Doubles
//
void IniFile::SetKeyValue_Doubles(const std::string& key, std::vector<double> values, const std::string& sectionName) {
    if (values.size() > 0) {
        string s;
        for (int i = 0; i < values.size(); ++i) {
            s += to_string(values[i]);
            if (i < values.size() - 1)
                s += ",";
        }
        SetKeyValue(key, s, sectionName);
    }
}

//
// IniFile::DeleteKey
//
bool IniFile::DeleteKey(const string& key, const string& sectionName) {
    if (SectionExists(sectionName))
        return FindSectionName(sectionName)->DeleteKey(key);
    else
        return false;
}

                //*******************************
                // IniFile Private
                //*******************************

//
// IniFile::FindSectionName
//
// returns an iterator to the section in the vector or end(iniSections) if the section was not found.
std::vector<IniFile::IniSection>::iterator IniFile::FindSectionName(const std::string& sectionName) {
    return ranges::find_if(iniSections, [&] (const IniSection& iniSection) { return CompareKeys(iniSection.sectionName, sectionName); } );
}

//
// IniFile::FindSectionName const
//
// returns an iterator to the section in the vector or end(iniSections) if the section was not found.
std::vector<IniFile::IniSection>::const_iterator IniFile::FindSectionName(const std::string& sectionName) const {
    return ranges::find_if(iniSections, [&] (const IniSection& iniSection) { return CompareKeys(iniSection.sectionName, sectionName); } );
}

                //*******************************
                // IniFile::IniSection
                //*******************************

//
// IniFile::IniSection::IniSection
//
IniFile::IniSection::IniSection(IniFile* _iniFile, const std::string& line) : iniFile(_iniFile), sectionLine(line) { 
    sectionName = sectionLine.section;
    if (line == "" || line == "[]")
        sectionLine.lineContainsASectionDefine = true;  // it's the dummy "" section
}

//
// IniFile::IniSection::KeyExists
//
bool IniFile::IniSection::KeyExists(const std::string& key) const {
    return values.count(iniFile->AdjustKeyCase(key)) > 0;
}

//
// IniFile::IniSection::GetKey
//
std::string IniFile::IniSection::GetKeyValue(const std::string& key) const {
    if (KeyExists(key))
        return values.at(iniFile->AdjustKeyCase(key));  // note: use at() instead of operator [] because of const
    else
        return "";  // key doesn't exist
}

//
// IniFile::IniSection::SetKeyValue
//
// if the key doesn't already exist, this will create it
void IniFile::IniSection::SetKeyValue(const std::string& key, const std::string& value) {
    if (!KeyExists(key)) {
        iniLines.emplace_back(key + " = " + value);
        values[iniFile->AdjustKeyCase(key)] = value;
    }
    else {
        auto it = FindKeyLine(key);
        if (it != end(iniLines)) {
            // try to adjust the whitespace before the comment if the size of the key value changes.
            // the result may not be in the correct column if you are using tabs instead of spaces.
            size_t oldSize = it->value.size();
            size_t newSize = value.size();
            if (oldSize > newSize) {
                it->whiteSpaceAfterValue += Spaces(oldSize - newSize);
            } else if (oldSize < newSize && ((newSize - oldSize) < it->whiteSpaceAfterValue.size())) {
                it->whiteSpaceAfterValue.erase(0, newSize - oldSize);
            }

            it->value = value;  // change the value text in the iniLine
        }
        values[key] = value;    // change the key value in the map
    }
}

//
// IniFile::FixPathSeparators
//
bool IniFile::FixPathSeparators(const std::string& iniFilePath) {
    IniFile iniFile(iniFilePath);
    bool changed = false;
    for (auto& section : iniFile.iniSections) {
        for (auto& keyPair : section.values) {
            string newValue = fixPathSeparators(keyPair.second);
            if (newValue != keyPair.second) {
                iniFile.SetKeyValue(keyPair.first, newValue, section.sectionName);
                changed = true;
            }
        }
    }
    if (changed)
        iniFile.Save();

    return changed;
}

//
// Get list of section names and key names
//

//
// GetSectionNames. Return the list of section names.
//
vector<string> IniFile::GetSectionNames() const {
    Strings ret;
    for (const auto& section : iniSections) {
        if (section.sectionName == "" && section.values.size() == 0)
            continue;   // skip section "" if it has no keys
        else {
            ret.emplace_back(section.sectionName);
        }
    }

    return ret;
}
 
//
// GetKeyNames Return the list of keys in a section.
//
std::vector<std::string> IniFile::GetKeyNamesInSection(const std::string& sectionName) const {
    Strings ret;
    const auto it = FindSectionName(sectionName);
    if (it != iniSections.end()) {
        const auto& values = it->values;
        ranges::for_each (values, [&] (const pair<string, string>& keypair) 
            { ret.emplace_back(keypair.first); });
    }

    return ret;
}
 
//
// GetKeyPairsInSection Return the list of keys in a section.
//
std::map<std::string, std::string> IniFile::GetKeyPairsInSection(const std::string& sectionName) const {
    std::map<std::string, std::string> ret;
    auto it = FindSectionName(sectionName);
    if (it != iniSections.end()) {
        ret = it->values;
    }

    return ret;
}

// 
// Return all the keys.
// Returns a vector of tuples of <string, string, string> = <section, key, value>
//
vector<tuple<string, string, string>> IniFile::GetAllKeyPairs() const {
    vector<tuple<string, string, string>> ret;
    for (const auto& section : iniSections) {
        if (section.sectionName == "" && section.values.size() == 0)
            continue;   // skip section "" if it has no keys
        else {
            for (const auto& keypair : section.values) {
                ret.emplace_back(make_tuple(section.sectionName, keypair.first, keypair.second));
            }
        }
    }

    return ret;
}
 
//
// IniFile::CompareKeys
//
bool IniFile::CompareKeys(const string& key1, const string& key2) const
{
    if (caseInsensitiveKeys)
        return lowerCase(key1) == lowerCase(key2);
    else
        return key1 == key2;
}

//
// IniFile::AdjustKeyCase
//
string IniFile::AdjustKeyCase(const string& key) const
{
    if (caseInsensitiveKeys)
        return lowerCase(key);
    else
        return key;
}

//
// IniFile::IniSection::DeleteKey
//
bool IniFile::IniSection::DeleteKey(const std::string& key) {
    if (KeyExists(key)) {
        values.erase(iniFile->AdjustKeyCase(key));
        auto it = FindKeyLine(key);
        if (it != end(iniLines))
            iniLines.erase(it);
        return true;
    } else
        return false;
}

//
// IniFile::IniSection::FindKeyLine
//
// returns end(iniLines) if not found
vector<IniFile::IniLine>::iterator IniFile::IniSection::FindKeyLine(const std::string& key) {
    return ranges::find_if(iniLines, [&] (const IniLine& iniLine) { return iniFile->CompareKeys(iniLine.key, key); } );
}

//
// IniFile::IniSection::FindKeyLine const
//
// returns end(iniLines) if not found
vector<IniFile::IniLine>::const_iterator IniFile::IniSection::FindKeyLine(const std::string& key) const {
    return ranges::find_if(iniLines, [&] (const IniLine& iniLine) { return iniFile->CompareKeys(iniLine.key, key); } );
}

                //*******************************
                // IniFile::IniLine
                //*******************************

//
// IniFile::IniLine::ParseLine
//
bool IniFile::IniLine::ParseLine(const string& _line) {
    string line = _line;    // line is modified as we find items and remove them

    // quoted strings isn't supported yet.  but here is some info.
    // to scan for a quoted string /"([^"\\]*(\\.[^"\\]*)*)"/
    // to scan for either single or double quoted strings /"([^"\\]*(\\.[^"\\]*)*)"|\'([^\'\\]*(\\.[^\'\\]*)*)\'/
    // https://stackoverflow.com/questions/249791/regex-for-quoted-string-with-escaping-quotes

    // save leading whitespaceGetAndRemoveLeadingWhitespace(&line);
    leadingWhiteSpace = GetAndRemoveLeadingWhitespace(&line);

    // if it is a section name
    bool hasSectionDefine = FoundLexExpr("^\\[[[:alnum:]]*\\]", line);     // [sectionName]
    if (hasSectionDefine) {
        lineContainsASectionDefine = true;
        line.erase(0, 1);   // remove "["
        section = FindLexExprMatch("^[[:alnum:]]*", line);    // sectionName
        line.erase(0, section.size() + 1);  // remove "name]"

        whiteSpaceAfterSection = GetAndRemoveLeadingWhitespace(&line);
        bool hasComment = FoundLexExpr("^[;]", line);          // ";"
        if (hasComment)
            comment = FindLexExprMatch("^[;].*", line);
        else if (line.size() > 0) {
            cerr << "Extra text in ini file = " << line << endl;
            return false;
        }

        return true;
    }

    // save the key.  save the value, if any.
    bool hasKey = (line.find('=') != string::npos) && FoundLexExpr("^[\\s]*[^=;]+", line);  // "key ="
    if (hasKey) {
        key = rtrim(line.substr(0, line.find('=')));    // "key"
        if (key.size() > 0) {
            line.erase(0, key.size());  // erase key from line
            whiteSpaceAfterKey = GetAndRemoveLeadingWhitespace(&line);  // get spaces before =
            assert(line.size() > 0);
            assert(line[0] == '=');
            line.erase(0, 1);   // erase the '='
            whiteSpaceBeforeValue = GetAndRemoveLeadingWhitespace(&line);   // get spaces before value if any
            if (line.size() > 0 && line[0] != ';') {
                value = FindLexExprMatch("^[^;]*[^\\s;]+", line);  // "value"
                line.erase(0, value.size());   // erase the value
                whiteSpaceAfterValue = GetAndRemoveLeadingWhitespace(&line);   // get spaces before value if any
            }
        }
    }

    bool hasComment = FoundLexExpr("^[;]", line);          // ";"
    if (hasComment) {
        comment = FindLexExprMatch("^[;].*", line);
    }
    else if (line.size() > 0) {
        cerr << "Extra text in ini file = " << line << endl;
        return false;
    }

    return true;
}

//
// IniFile::IniLine::RebuildLine
//
string IniFile::IniLine::RebuildLine() const {
    string line;

    line += leadingWhiteSpace;

    if (lineContainsASectionDefine) {
        if (section != "") {
            line += "[" + section + "]" + whiteSpaceAfterSection + comment;
        }
    } else {
        line += key + whiteSpaceAfterKey;
        if (key != "")
            line += "=";
        line += whiteSpaceBeforeValue + value + whiteSpaceAfterValue + comment;
    }

    return line;
}

//
// IniFile::IniLine::GetAndRemoveLeadingWhitespace
//
string IniFile::IniLine::GetAndRemoveLeadingWhitespace(string* line) const {
    string ws = FindLexExprMatch("^[[:space:]]+", *line);
    if (ws.size() > 0)
        line->erase(0, ws.size());

    return ws;
}

                //*******************************
                //ostream& operator << (ostream& os, const IniFile&);
                //*******************************

//
// operator <<
//
ostream& operator << (ostream& os, const IniFile& iniFile) {
    // output any empty theme keys at the top
    auto it = iniFile.FindSectionName("");  // find any "" theme
    if (it != iniFile.iniSections.end()) {
        for(const auto& iniLine : it->iniLines) {
            os << iniLine.RebuildLine() << endl;
        }
    }

    for (const auto& section : iniFile.iniSections) {
        if (section.sectionName != "") {
            os << section.sectionLine.RebuildLine() << endl;

            for(const auto& iniLine : section.iniLines) {
                os << iniLine.RebuildLine() << endl;
            }
        }
    }

    return os;
}
