#pragma once

#include "pugixml.hpp"
#include "Str.h"

struct Tau_Xml : public pugi::xml_document {
    std::string xmlFilePath;                    // the saved filePath from the Load() call

    Tau_Xml() {}
    Tau_Xml(const std::string& filePath) { Load(filePath); }

    pugi::xml_parse_result Load(const std::string& filePath);     // loads the xml from a file and saves the filename in xmlFilePath
    bool Save();                                // saves the xml to xmlFilePath
    bool SaveAs(const std::string& filePath);   // saves the xml to passed filePath
    void Clear();

    // finds a node in the hierarchy starting from the root of the document.  returns an empty node if not found.
    static pugi::xml_node Find(pugi::xml_node& startNode, const Tau::Strings& nodeNames);
    pugi::xml_node Find(const Tau::Strings& nodeNames);

    static std::string NodeToXmlString(const pugi::xml_node& node);
};