#include "IniFile.h"
#include <regex>
#include "Str.h"
#include "Sep.h"
#include "DirFile.h"
#include <assert.h>
#include <iostream>
#include <fstream>

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

IniFile::IniFile() {
}

IniFile::IniFile(const string& _iniFilePath) {
    Load(_iniFilePath);
}

bool IniFile::Load(const string& _iniFilePath) {
    bool success = false;
    iniFilePath = _iniFilePath;

    Strings fileLines = ReadTextFileAsAStringArray(iniFilePath, /*removeCRLF*/ true);

    // add a dummy "" section for keys that aren't inside a section.  the saved "[]" is not written to the file.  
    // any keys not in a section are written to the top of the file with no section name above them.
    iniSections.emplace_back("");

    for (const auto& fileLine : fileLines) {
        IniLineInfo iniLineInfo(fileLine);      // scan the line for a section name, key, value, and comment

        if (!iniLineInfo.section.empty()) {
            // if the line is a new section add the section name to the section list
            iniSections.emplace_back(fileLine);
        } else {
            // if the line has a key definition, add it to the map of key/value pairs
            if (!iniLineInfo.key.empty())
                iniSections.back().values[iniLineInfo.key] = iniLineInfo.value;

            // add the line info to the list of lines and map of keys in the current/last section
            iniSections.back().iniLineInfos.emplace_back(iniLineInfo);
        }
    }

    return success;
}

bool IniFile::Save() {
    ofstream ofile(iniFilePath.c_str(), ofstream::out | ofstream::trunc);
    if (!ofile.is_open())
        return false;

    ofile << *this;
    ofile.close();

    return true;
}

bool IniFile::SaveAs(const string& filePath) {
    ofstream ofile(filePath.c_str(), ofstream::out | ofstream::trunc);
    if (!ofile.is_open())
        return false;

    ofile << *this;
    ofile.close();

    return true;
}

void IniFile::Clear() {
    iniSections.clear();
}

                //*******************************
                // IniFile Private
                //*******************************

// returns end(iniSections) if not found
std::vector<IniFile::IniSection>::iterator IniFile::FindSectionName(const std::string& sectionName) {
    return find_if(begin(iniSections), end(iniSections), [&] (const IniSection& iniSection) { return iniSection.sectionName == sectionName; } );
}

bool IniFile::SectionExists(const std::string& sectionName) {
    return FindSectionName(sectionName) != end(iniSections);
}

bool IniFile::KeyExists(const string& key, const string& sectionName) {
    if (SectionExists(sectionName))
        return FindSectionName(sectionName)->KeyExists(key);
    else
        return false;
}

string IniFile::GetKeyValue(const string& key, const string& sectionName) {
    auto it = FindSectionName(sectionName);
    if (it != end(iniSections))
        return it->GetKey(key);
    else
        return "";
}

// if the key doesn't already exist, this will create it
// if the sectionName doesn't already exist, this will create it
void IniFile::SetKeyValue(const string& key, const string& value, const string& sectionName) {
    if (!SectionExists(sectionName))
        iniSections.emplace_back(string("[") + sectionName + "]");

    FindSectionName(sectionName)->SetKey(key, value);
}

bool IniFile::DeleteKey(const string& key, const string& sectionName) {
    if (SectionExists(sectionName))
        return FindSectionName(sectionName)->DeleteKey(key);
    else
        return false;
}

                //*******************************
                // IniFile::IniSection
                //*******************************

IniFile::IniSection::IniSection(const std::string& line) : sectionLine(line) { 
    sectionName = sectionLine.section;
    if (line == "")
        sectionLine.lineContainsASectionDefine = true;  // it's the dummy "" section
}

bool IniFile::IniSection::KeyExists(const std::string& key) {
    return values.count(key) > 0;
}

std::string IniFile::IniSection::GetKey(const std::string& key) {
    if (KeyExists(key))
        return values[key];
    else
        return "";  // key doesn't exist
}

// if the key doesn't already exist, this will create it
void IniFile::IniSection::SetKey(const std::string& key, const std::string& value) {
    if (!KeyExists(key)) {
        iniLineInfos.emplace_back(key + " = " + value);
        values[key] = value;
    }
    else {
        auto it = FindKeyLine(key);
        if (it != end(iniLineInfos)) {
            // try to adjust the whitespace before the comment if the size of the key value changes.
            // the result may not be in correct column if you are using tabs instead of spaces.
            int oldSize = it->value.size();
            int newSize = value.size();
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

///
/// @brief Fix any / or \ path separators to be correct for the OS.
/// @param iniFilePath - the path of the ini file
/// @return true if any key was changed and the ini file rewritten
/// 
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

bool IniFile::IniSection::DeleteKey(const std::string& key) {
    if (KeyExists(key)) {
        values.erase(key);
        auto it = FindKeyLine(key);
        if (it != end(iniLineInfos))
            iniLineInfos.erase(it);
        return true;
    } else
        return false;
}

// returns end(iniLineInfos) if not found
vector<IniFile::IniLineInfo>::iterator IniFile::IniSection::FindKeyLine(const std::string& key) {
    return find_if(begin(iniLineInfos), end(iniLineInfos), [&] (IniLineInfo& iniLineInfo) { return iniLineInfo.key == key; } );
}

                //*******************************
                // IniFile::IniLineInfo
                //*******************************

bool IniFile::IniLineInfo::scanLine(const string& _line) {
    string line = _line;    // line is modified as we find items and remove them
cout << line << endl;

// to scan for a quoted string /"([^"\\]*(\\.[^"\\]*)*)"/
// to scan for either single or double quoted strings /"([^"\\]*(\\.[^"\\]*)*)"|\'([^\'\\]*(\\.[^\'\\]*)*)\'/
//https://stackoverflow.com/questions/249791/regex-for-quoted-string-with-escaping-quotes

    // save leading whitespaceGetAndRemoveLeadingWhitespace(&line);
    leadingWhiteSpace = GetAndRemoveLeadingWhitespace(&line);

    // if it is a section name
    bool hasSectionDefine = FoundLexExpr("^\\[[[:alnum:]]+\\]", line);     // [sectionName]
    if (hasSectionDefine) {
        lineContainsASectionDefine = true;
        line.erase(0, 1);   // remove "["
        section = FindLexExprMatch("^[[:alnum:]]+", line);    // sectionName
        line.erase(0, section.size() + 1);  // remove "name]"

        whiteSpaceAfterSection = GetAndRemoveLeadingWhitespace(&line);
        bool hasComment = FoundLexExpr("^[;#]", line);          // ";" or "#"
        if (hasComment)
            comment = FindLexExprMatch("^[;#].*", line);
        else if (line.size() > 0) {
            cerr << "Extra text in ini file = " << line << endl;
            return false;
        }

        return true;
    }

    // save the key.  save the value, if any.
    bool hasKey = FoundLexExpr("^[[:alnum:]_-]+[[:space:]]*=", line);  // "key ="
    if (hasKey) {
        key = FindLexExprMatch("^[[:alnum:]_-]+", line);  // "key"
        if (key.size() > 0) {
            line.erase(0, key.size());  // erase key from line
            whiteSpaceAfterKey = GetAndRemoveLeadingWhitespace(&line);  // get spaces before =
            assert(line.size() > 0);
            assert(line[0] == '=');
            line.erase(0, 1);   // erase the '='
            whiteSpaceBeforeValue = GetAndRemoveLeadingWhitespace(&line);   // get spacces before value if any
            if (line.size() > 0) {
                value = FindLexExprMatch("^[^[:space:];#]+", line);  // "value"
                line.erase(0, value.size());   // erase the value
                whiteSpaceAfterValue = GetAndRemoveLeadingWhitespace(&line);   // get spacces before value if any
            }
        }
    }

    bool hasComment = FoundLexExpr("^[;#]", line);          // ";" or "#"
    if (hasComment) {
        comment = FindLexExprMatch("^[;#].*", line);
    }
    else if (line.size() > 0) {
        cerr << "Extra text in ini file = " << line << endl;
        return false;
    }

    return true;
}

string IniFile::IniLineInfo::rebuildLine() const {
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

// column starts at 0
void IniFile::IniLineInfo::padToCommentColumn(std::string* line, int column) const {
    int padCount = column - (int) line->size();
    if (padCount < 0)
        padCount = 0;

    if (padCount == 0 && line->size() > 0)
        padCount = 0;           // leave a one space gap between the existing string and the comment

    if (padCount > 0)
        *line += string(padCount, ' ');
}

string IniFile::IniLineInfo::GetAndRemoveLeadingWhitespace(string* line) const {
    string ws = FindLexExprMatch("^[[:space:]]+", *line);
    if (ws.size() > 0)
        line->erase(0, ws.size());

    return ws;
}

                //*******************************
                //ostream& operator << (ostream& os, const IniFile&);
                //*******************************

ostream& operator << (ostream& os, const IniFile& iniFile) {
    for (const auto& section : iniFile.iniSections) {
        if (section.sectionName != "")
            os << section.sectionLine.rebuildLine() << endl;

        for(const auto& iniLineInfo : section.iniLineInfos) {
            os << iniLineInfo.rebuildLine() << endl;
        }
    }

    return os;
}
