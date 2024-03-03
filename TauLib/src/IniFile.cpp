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
                // IniLine
                //*******************************

//
// IniLine::ParseLine
//
bool IniLine::ParseLine(const string& _line) {
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
// IniLine::RebuildLine
//
string IniLine::RebuildLine() const {
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
// IniLine::GetAndRemoveLeadingWhitespace
//
string IniLine::GetAndRemoveLeadingWhitespace(string* line) const {
    string ws = FindLexExprMatch("^[[:space:]]+", *line);
    if (ws.size() > 0)
        line->erase(0, ws.size());

    return ws;
}

                //*******************************
                //ostream& operator << (ostream& os, const IniLine&);
                //*******************************

//
// operator <<
//
std::ostream& operator<<(std::ostream& os, const IniLine& iniLine)
{
    os << iniLine.RebuildLine() << endl;;
    return os;
}

                //*******************************
                // IniSection
                //*******************************

//
// IniSection::IniSection
//
IniSection::IniSection(IniFile* _iniFile, const std::string& line) : iniFile(_iniFile), sectionLine(line) { 
    sectionName = sectionLine.section;
    if (line == "" || line == "[]")
        sectionLine.lineContainsASectionDefine = true;  // it's the dummy "" section
}

//
// IniSection::KeyExists
//
bool IniSection::KeyExists(const std::string& key) const {
    return values.count(key) > 0;
}

//
// IniSection::GetKey
//
std::string IniSection::GetKeyValue(const std::string& key) const {
    if (KeyExists(key))
        return values.at(key);  // note: use at() instead of operator [] because of const
    else
        return "";  // key doesn't exist
}

//
// IniSection::SetKeyValue
//
// if the key doesn't already exist, this will create it
void IniSection::SetKeyValue(const std::string& key, const std::string& value) {
    if (!KeyExists(key)) {
        iniLines.emplace_back(key + " = " + value);
        values[key] = value;
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

                //*******************************
                //ostream& operator << (ostream& os, const IniSection&);
                //*******************************

//
// operator <<
//
std::ostream& operator<<(std::ostream& os, const IniSection& iniSection)
{
    os << iniSection.sectionLine;
    ranges::for_each(iniSection.iniLines, [&] (const IniLine& iniLine) { os << iniLine; });
    return os;
}

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
                iniSections.back().values[iniLine.key] = iniLine.value;

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
bool IniFile::Save() {
    if (iniFilePath == "")
        return false;

    return SaveAs(iniFilePath);
}

//
// IniFile::SaveAs
//
bool IniFile::SaveAs(const string& filePath) {
    ofstream ofile(filePath.c_str(), ofstream::out | ofstream::trunc);
    if (!ofile.is_open())
        return false;

    SortSectionKeys();  // sort the keys in each section

    // output any empty theme keys at the top
    auto it = FindSectionName("");  // find any "" theme
    if (it != iniSections.end()) {
        for(const auto& iniLine : it->iniLines) {
            ofile << iniLine.RebuildLine() << endl;
        }
    }

    for (const auto& section : iniSections) {
        if (section.sectionName != "") {
            ofile << section.sectionLine.RebuildLine() << endl;

            for(const auto& iniLine : section.iniLines) {
                ofile << iniLine.RebuildLine() << endl;
            }
        }
    }
    ofile.close();

    return true;
}

//
// IniFile::SortSectionKeys
//
void IniFile::SortSectionKeys()
{
    for (auto& section : iniSections) {
        section.SortIniLines();
    }
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
void IniFile::SetKeyValue_Ints(const std::string& key, const std::vector<int>& values, const std::string& sectionName) {
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
void IniFile::SetKeyValue_Floats(const std::string& key, const std::vector<float>& values, const std::string& sectionName) {
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
void IniFile::SetKeyValue_Doubles(const std::string& key, const std::vector<double>& values, const std::string& sectionName) {
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


// get objects from Tau_Rect.h
Tau_Point IniFile::GetKeyValue_Tau_Point(const std::string& key, const std::string& sectionName) const
{
    vector<int> ints = GetKeyValue_Ints(key, sectionName);
    Tau_Point point;
    assert(ints.size() == 2);
    if (ints.size() == 2) {
        point.x = ints[0];
        point.y = ints[1];
    }

    return point;
}

Tau_Size IniFile::GetKeyValue_Tau_Size(const std::string& key, const std::string& sectionName) const
{
    vector<int> ints = GetKeyValue_Ints(key, sectionName);
    Tau_Size size;
    assert(ints.size() == 2);
    if (ints.size() == 2) {
        size.w = ints[0];
        size.h = ints[1];
    }

    return size;
}

Tau_Rect IniFile::GetKeyValue_Tau_Rect(const std::string& key, const std::string& sectionName) const
{
    vector<int> ints = GetKeyValue_Ints(key, sectionName);
    Tau_Rect rect;
    assert(ints.size() == 4);
    if (ints.size() == 4) {
        rect.x = ints[0];
        rect.y = ints[1];
        rect.w = ints[2];
        rect.h = ints[3];
    }

    return rect;
}

Tau_Posit IniFile::GetKeyValue_Tau_Posit(const std::string& key, const std::string& sectionName) const
{
    vector<int> ints = GetKeyValue_Ints(key, sectionName);
    Tau_Posit posit;
    assert(ints.size() == 2);
    if (ints.size() == 2) {
        posit.x = ints[0];
        posit.y = ints[1];
    }

    return posit;
}

// get objects from Tau_Color.h
Tau_RGB IniFile::GetKeyValue_Tau_RGB(const std::string& key, const std::string& sectionName) const
{
    vector<int> ints = GetKeyValue_Ints(key, sectionName);
    Tau_RGB color;
    assert(ints.size() == 3);
    if (ints.size() == 3) {
        color.r = ints[0];
        color.g = ints[1];
        color.b = ints[2];
    }

    return color;
}

Tau_Color IniFile::GetKeyValue_Tau_Color(const std::string& key, const std::string& sectionName) const
{
    vector<int> ints = GetKeyValue_Ints(key, sectionName);
    Tau_Color color;
    assert(ints.size() == 4);
    if (ints.size() == 4) {
        color.r = ints[0];
        color.g = ints[1];
        color.b = ints[2];
        color.a = ints[3];
    }

    return color;
}

// get objects from imgui.h
ImVec2 IniFile::GetKeyValue_ImVec2(const std::string& key, const std::string& sectionName) const
{
    vector<float> floats = GetKeyValue_Floats(key, sectionName);
    ImVec2 invec2;
    assert(floats.size() == 2);
    if (floats.size() == 2) {
        invec2.x = floats[0];
        invec2.y = floats[1];

    }

    return invec2;
}

ImVec4 IniFile::GetKeyValue_ImVec4(const std::string& key, const std::string& sectionName) const
{
    vector<float> floats = GetKeyValue_Floats(key, sectionName);
    ImVec4 invec4;
    assert(floats.size() == 4);
    if (floats.size() == 4) {
        invec4.x = floats[0];
        invec4.y = floats[1];
        invec4.z = floats[2];
        invec4.w = floats[3];
    }

    return invec4;
}

// in ImGui ImVec4 (4 floats between 0.0-1.0 are used for color values instead of integer 0-255)
ImVec4 IniFile::GetKeyValue_Tau_Color_as_ImVec4(const std::string& key, const std::string& sectionName) const
{
    Tau_Color color = GetKeyValue_Tau_Color(key, sectionName);
    ImVec4 imvec4;
    imvec4.x = ((float) color.r) / 255.0f;
    imvec4.y = ((float) color.g) / 255.0f;
    imvec4.z = ((float) color.b) / 255.0f;
    imvec4.w = ((float) color.a) / 255.0f;

    return imvec4;
}

// in ImGui ImVec4 (4 floats between 0.0-1.0 are used for color values instead of integer 0-255)
ImVec4 IniFile::GetKeyValue_Tau_RGB_as_ImVec4(const std::string& key, const std::string& sectionName) const
{
    Tau_RGB rgb = GetKeyValue_Tau_RGB(key, sectionName);
    ImVec4 imvec4;
    imvec4.x = ((float) rgb.r) / 255.0f;
    imvec4.y = ((float) rgb.g) / 255.0f;
    imvec4.z = ((float) rgb.b) / 255.0f;
    imvec4.w = 1.0f;

    return imvec4;

}

// set objects from Tau_Rect.h
void IniFile::SetKeyValue_Tau_Point(const std::string& key, const Tau_Point& point, const std::string& sectionName)
{
    vector<int> ints {point.x, point.y};
    SetKeyValue_Ints(key, ints, sectionName);
}

void IniFile::SetKeyValue_Tau_Size(const std::string& key, const Tau_Size& size, const std::string& sectionName)
{
    vector<int> ints {size.w, size.h};
    SetKeyValue_Ints(key, ints, sectionName);
}

void IniFile::SetKeyValue_Tau_Rect(const std::string& key, const Tau_Rect& rect, const std::string& sectionName)
{
    vector<int> ints {rect.x, rect.y, rect.w, rect.h};
    SetKeyValue_Ints(key, ints, sectionName);
}

void IniFile::SetKeyValue_Tau_Posit(const std::string& key, const Tau_Posit& posit, const std::string& sectionName)
{
    vector<int> ints {posit.x, posit.y};
    SetKeyValue_Ints(key, ints, sectionName);
}

// set objects from Tau_Color.h
void IniFile::SetKeyValue_Tau_RGB(const std::string& key, const Tau_RGB& rgb, const std::string& sectionName)
{
    vector<int> ints {rgb.r, rgb.g, rgb.b};
    SetKeyValue_Ints(key, ints, sectionName);
}

void IniFile::SetKeyValue_Tau_Color(const std::string& key, const Tau_Color& color, const std::string& sectionName)
{
    vector<int> ints {color.r, color.g, color.b, color.a};
    SetKeyValue_Ints(key, ints, sectionName);
}

// set objects from imgui.h
void IniFile::SetKeyValue_ImVec2(const std::string& key, const ImVec2& imvec2, const std::string& sectionName)
{
    vector<float> floats {imvec2.x, imvec2.y};
    SetKeyValue_Floats(key, floats, sectionName);
}

void IniFile::SetKeyValue_ImVec4(const std::string& key, const ImVec4& imvec4, const std::string& sectionName)
{
    vector<float> floats {imvec4.x, imvec4.y, imvec4.z, imvec4.w};
    SetKeyValue_Floats(key, floats, sectionName);
}

// in ImGui ImVec4 (4 floats between 0.0-1.0 are used for color values instead of integer 0-255)
void IniFile::SetKeyValue_ImVec4_as_Tau_Color(const std::string& key, const ImVec4& imvec4, const std::string& sectionName)
{
    Tau_Color color;
    color.r = (int) round(imvec4.x * 255.0);
    color.g = (int) round(imvec4.y * 255.0);
    color.b = (int) round(imvec4.z * 255.0);
    color.a = (int) round(imvec4.w * 255.0);

    SetKeyValue_Tau_Color(key, color, sectionName);
}

// in ImGui ImVec4 (4 floats between 0.0-1.0 are used for color values instead of integer 0-255)
void IniFile::SetKeyValue_ImVec4_as_Tau_RGB(const std::string& key, const ImVec4& imvec4, const std::string& sectionName)
{
    Tau_RGB rgb;
    rgb.r = (int) round(imvec4.x * 255.0);
    rgb.g = (int) round(imvec4.y * 255.0);
    rgb.b = (int) round(imvec4.z * 255.0);
    // imvec4.w is not used

    SetKeyValue_Tau_RGB(key, rgb, sectionName);
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
// FindSectionName
//
// returns an iterator to the section in the vector or end(iniSections) if the section was not found.
std::vector<IniSection>::iterator IniFile::FindSectionName(const std::string& sectionName) {
    return ranges::find_if(iniSections, [&] (const IniSection& iniSection) { return CompareKeysEqual(iniSection.sectionName, sectionName); } );
}

//
// IniFile::FindSectionName const
//
// returns an iterator to the section in the vector or end(iniSections) if the section was not found.
std::vector<IniSection>::const_iterator IniFile::FindSectionName(const std::string& sectionName) const {
    return ranges::find_if(iniSections, [&] (const IniSection& iniSection) { return CompareKeysEqual(iniSection.sectionName, sectionName); } );
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
Tau::Strings IniFile::GetKeyNamesInSection(const std::string& sectionName) const {
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
// IniFile::CompareKeysEqual
//
bool IniFile::CompareKeysEqual(const string& key1, const string& key2) const
{
    return key1 == key2;
}

//
// IniFile::CompareKeysSort
//
bool IniFile::CompareKeysSort(const string& key1, const string& key2) const
{
    return key1 < key2;
}

//
// IniSection::DeleteKey
//
bool IniSection::DeleteKey(const std::string& key) {
    if (KeyExists(key)) {
        values.erase(key);
        auto it = FindKeyLine(key);
        if (it != end(iniLines))
            iniLines.erase(it);
        return true;
    } else
        return false;
}

//
// IniSection::FindKeyLine
//
// returns end(iniLines) if not found
vector<IniLine>::iterator IniSection::FindKeyLine(const std::string& key) {
    return ranges::find_if(iniLines, [&] (const IniLine& iniLine) { return iniFile->CompareKeysEqual(iniLine.key, key); } );
}

//
// IniSection::FindKeyLine const
//
// returns end(iniLines) if not found
vector<IniLine>::const_iterator IniSection::FindKeyLine(const std::string& key) const {
    return ranges::find_if(iniLines, [&] (const IniLine& iniLine) { return iniFile->CompareKeysEqual(iniLine.key, key); } );
}

void IniSection::SortIniLines()
{
    // sort the iniLines by key
    ranges::sort(iniLines,
                 [&] (const IniLine& iniLine1, const IniLine& iniLine2) { return iniFile->CompareKeysSort(iniLine1.key, iniLine2.key); } );
}

                //*******************************
                //ostream& operator << (ostream& os, const IniFile&);
                //*******************************

//
// operator <<
//
std::ostream& operator<<(std::ostream& os, const IniFile& iniFile)
{
    ranges::for_each(iniFile.iniSections, [&] (const IniSection& iniSection) { os << iniSection; });
    return os;
}
