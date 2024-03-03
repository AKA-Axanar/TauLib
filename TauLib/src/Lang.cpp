///
/// @file
/// @brief CPP file for Lang class.
/// @author screemer.  modified by Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

#include "Lang.h"
#include <fstream>
#include <iostream>
#include "Str.h"
#include "Sep.h"
#include "DirFile.h"
#include <assert.h>

using namespace std;

//*******************************
// string _(string input)
//*******************************
string _(const string & input) {
    shared_ptr<Lang> lang(Lang::GetInstance());

    return lang->Translate(input);
}

//*******************************
// Lang::LoadLanguage
//*******************************
void Lang::LoadLanguage(string languageName) {
    assert(langDir != "");
    if (langDir == "")
        cerr << "langDir has not been set" << endl;

    string path = langDir + Tau::sep + languageName + ".txt";
    langData.clear();
    newData.clear();
    currentLang = languageName;
    if (languageName == "English") return;

    ifstream is(path);
    string line;
    Tau::Strings lines;
    int lineNum = 0;
    while (std::getline(is, line)) {
        // if this is the first line of the file and the beginning of the string contains the UTF-8 header
        // strip the UTF-8 header off
        if (lineNum == 0 && line.size() >= 3) {
            unsigned char* p = (unsigned char*) line.c_str();
            if ((p[0] == 0xEF) && (p[1] == 0xBB) && (p[2] == 0xBF)) {
                string skipUTF8Header =  (char*) p + 3;
                line = skipUTF8Header;
            }
        }
        lines.push_back(line);
        ++lineNum;
    }
    for (int i = 0; i < lines.size(); i += 2) {
        if (i+1<lines.size()) {
            langData[lines[i]] = lines[i + 1];
        }
    }
    is.close();
}

//*******************************
// Lang::Translate
//*******************************
string Lang::Translate(string input){
    if (currentLang == "English")
        return input;

    Tau::trim(&input);

    if (input.empty()) 
        return "";

    string translated = langData[input];
    if (translated == "") {
        langData[input] = input;
        translated = input;
        newData.push_back(input);
    }
    return translated;
}

//*******************************
// Lang::Dump
//*******************************
void Lang::Dump(string fileName) {

    string fileSave = langDir + Tau::sep + fileName;
    map<string, string>::iterator it;

    ofstream os(fileSave);
    for (const string& data:newData) {
        cout << data << endl;
        os << data << endl << data << endl;
    }
    os.flush();
    os.close();
}

//*******************************
// Lang::GetListOfLanguages
// Writes newData to a file and to cout
//*******************************
vector<string> Lang::GetListOfLanguages()
{
    vector<string> languages;
    languages.push_back("English");
    Tau::Strings filenames = Tau::GetFileNamesInDir(langDir);
    for (auto const& name : filenames)
    {
        // if it's a*.txt file but not English.txt, add it to the list of languages
        if (Tau::GetFileExtensionWithoutDot(name) == "txt" && ! Tau::icompareBool(name, "English.txt"))
        {
            languages.push_back(Tau::GetFilenameBase(name));
        }
    }
    return languages;
}
