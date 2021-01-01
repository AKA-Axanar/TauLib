//
// Created by screemer on 2/4/19.
// modified by Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
//
#pragma once

#include <map>
#include <string>
#include <memory>
#include <vector>

/// @brief The key routine for doing language translations.  An outside program scans the .h and .cpp files for _("xxxxx") strings
/// and write them double spaced to the file English.txt.  English text is on the odd numbered lines.  The even numbered lines are blank in file English.txt.
/// Translators start with a copy of English.txt and add the translated text on the even numbered lines and rename the file to their language.
/// 
std::string _(const std::string & input);

//******************
// Lang
//******************
class Lang {
public:
    std::string langDir;                    ///< The dir containing French.txt, Deutsch.txt, Spanish.txt, etc
    std::string currentLang {"English"};    ///< The name of the current language

    /// @brief Finds the language file and loads the map
    /// @param languageName 
    void LoadLanguage(std::string languageName);    // the filename without the .txt

    /// @brief Translates the string to the current language by looking up the english text in the map.
    /// @param input 
    /// @return The translated string.  The original English text is returned if the translation line is not in the file.
    std::string Translate(std::string input);

    /// @brief Returns a list of the languages found in the translations directory.
    /// @return The returned strings are the language names only.  The ".txt" is stripped from the file name.
    std::vector<std::string> GetListOfLanguages();

    // Lang is a singleton class object so public constructors do not exist.
    Lang(const Lang&) = delete;
    Lang& operator=(const Lang&) = delete;

    /// @brief Lang is a singleton - return a single shared global object of Lang.
    static std::shared_ptr<Lang> GetInstance() {
        static std::shared_ptr<Lang> s{new Lang};
        return s;
    }

    /// @brief Writes newData to a file and to cout
    /// @param fileName 
    void Dump(std::string fileName);

private:
    /// @brief A private constructor for GetInstance
    Lang() {};
    std::map<std::string,std::string> langData;     ///< A map of English to current language
    std::vector<std::string> newData;               ///< Strings that are missing from the translation file
};
