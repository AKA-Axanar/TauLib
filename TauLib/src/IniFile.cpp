#include "IniFile.h"
#include <regex>
#include "Str.h"
#include "sep.h"
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

        if (!iniLineInfo.sectionDefine.empty()) {
            // if start of a new section add the section name to the section list
            iniSections.emplace_back(fileLine);
        } else {
            // add the line info to the list of lines in the current section
            iniSections.back().iniLineInfos.emplace_back(iniLineInfo);
            // if the line has a key definition, add it to the map of key/value pairs
            if (!iniLineInfo.key.empty())
                iniSections.back().values[iniLineInfo.key] = iniLineInfo.value;
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
        if (it != end(iniLineInfos))
            it->value = value;
        values[key] = value;
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
    return find_if(begin(iniLineInfos), end(iniLineInfos), [&] (const IniLineInfo& iniLineInfo) { return iniLineInfo.key == key; } );

}

                //*******************************
                // IniFile::IniLineInfo
                //*******************************

void IniFile::IniLineInfo::scanLine(const string& _line) {
    string line = _line;    // line is modified as we find items and remove them

    // test for blank line
    if (FoundLexExpr("^[[:space:]]*$", line)) {
        return; // blank line
    }

    // test if only a comment on the line
    if (FoundLexExpr("^[[:space:]]*;", line)) {
        // only a comment on the line
        string ws = GetAndRemoveLeadingWhitespace(&line);
        commentColumn = (int) ws.size();
        comment = line;
        return;
    }

    // there is other text on the line
    // if there is a comment find the column, save and remove the comment.
    // removing the comment simplifies the rest
    bool hasComment = FoundLexExpr("^.*;", line);                  // "key = value     ;"
    if (hasComment) {
        commentColumn = (int) FindLexExprMatch("^.*;", line).size() - 1;   // "key = value     ;"
        assert(commentColumn >= 0);
        comment = line.substr(commentColumn);   // ";comment"
        line.erase(commentColumn);              // erase the comment from the string
    }

    // continue.  scan any text prior to the comment.

    // if it is a section name
    bool hasSectionDefine = FoundLexExpr("^\\[[[:alnum:]]+\\]", line);     // [sectionName]
    if (hasSectionDefine) {
        line.erase(0, 1);   // remove [
        sectionDefine = FindLexExprMatch("^[[:alnum:]]+", line);    // sectionName
        return;
    }
    // if not a section name, continue to scan for "key = value" or "key = "

    // save the key.  save the value, if any.
    bool hasKey = FoundLexExpr("^[[:alnum:]_-]+[[:space:]]*=", line);  // "key ="
    if (hasKey) {
        key = FindLexExprMatch("^[[:alnum:]_-]+", line);  // "key"
        if (key.size() > 0) {
            line.erase(0, key.size());
            whiteSpaceAfterKey = GetAndRemoveLeadingWhitespace(&line);
            assert(line.size() > 0);
            assert(line[0] == '=');
            line.erase(0, 1);   // erase the '='
            whiteSpaceBeforeValue = GetAndRemoveLeadingWhitespace(&line);
            if (line .size() > 0) {
                value = FindLexExprMatch("^[^[:space:]]+", line);  // "value"
            }
        }
        return;
    }

    // if not blank, not a section, no key, no comment, and something is left
    if (!comment.empty())
        cout << "Invalid ini line: " << _line << endl;
}

string IniFile::IniLineInfo::rebuildLine() const {
    string line;
    if (sectionDefine != "")
        line += "[" + sectionDefine + "]";
    else if (!key.empty()) {
        line += key;
        line += whiteSpaceAfterKey;
        line += '=';
        if (!value.empty()) {
            line += whiteSpaceBeforeValue;
            line += value;
        }
    }

    if (!comment.empty()) {
        padToCommentColumn(&line, commentColumn);
        line += comment;
    }

    return line;
}

// column starts at 0
void IniFile::IniLineInfo::padToCommentColumn(std::string* line, int column) const {
    int padCount = column - (int) line->size();
    if (padCount < 0)
        padCount = 0;

    if (padCount == 0 && line->size() > 0)
        padCount = 1;           // leave a one space gap between the existing string and the comment

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
