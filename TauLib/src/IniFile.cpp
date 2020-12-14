#include "IniFile.h"
#include <regex>

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
}

bool IniFile::Load(const string& _iniFilePath) {
    bool success = false;

    return success;
}

bool IniFile::Save() {
    bool success = false;

    return success;
}

bool IniFile::SaveAs(const string& _iniFilePath) {
    bool success = false;

    return success;
}

void IniFile::Clear() {
    iniSections.clear();
}

                //*******************************
                // IniFile Private
                //*******************************

// returns end(iniSections) if not found
std::vector<IniFile::IniSection>::iterator IniFile::FindSection(const std::string& sectionName) {
    return find_if(begin(iniSections), end(iniSections), [&] (const IniSection& iniSection) { return iniSection.sectionName == sectionName; } );
}

bool IniFile::SectionExists(const std::string& sectionName) {
    return FindSection(sectionName) != end(iniSections);
}

bool IniFile::KeyExists(const string& sectionName, const string& key) {
    if (SectionExists(sectionName))
        return FindSection(sectionName)->KeyExists(key);
    else
        return false;
}

string IniFile::GetKey(const string& sectionName, const string& key) {
    if (SectionExists(sectionName))
        return FindSection(sectionName)->GetKey(key);
    else
        return "";
}

// if the key doesn't already exist, this will create it
// if the sectionName doesn't already exist, this will create it
void IniFile::SetKey(const string& sectionName, const string& key, const string& value) {
    if (!SectionExists(sectionName))
        iniSections.emplace_back(IniSection(sectionName));

    FindSection(sectionName)->SetKey(key, value);
}

bool IniFile::DeleteKey(const string& sectionName, const string& key) {
    if (SectionExists(sectionName))
        return FindSection(sectionName)->DeleteKey(key);
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
    values[key] = value;
}

bool IniFile::IniSection::DeleteKey(const std::string& key) {
    if (KeyExists(key)) {
        values.erase(key);
        return true;
    } else
        return false;
}

                //*******************************
                // Dump
                //*******************************

#ifdef _DEBUG
void IniFile::Dump() {
}

#endif
