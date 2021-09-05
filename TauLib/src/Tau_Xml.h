#pragma once
///
/// @file
/// @brief Header file for Tau_Xml.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

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

    // add a tag/value pair in one call
    pugi::xml_node AppendChild(pugi::xml_node& parent, const std::string& tagName, const std::string& value);

    // insert a tag/value pair before a child node in one call
    pugi::xml_node InsertChildBefore(pugi::xml_node& parent, const std::string& tagName, const std::string& value, pugi::xml_node& beforeNode);

    // insert a tag/value pair after a child node in one call
    pugi::xml_node InsertChildAfter(pugi::xml_node& parent, const std::string& tagName, const std::string& value, pugi::xml_node& afterNode);

    // finds a node in the hierarchy starting from the root of the document.  returns an empty node if not found.
    static pugi::xml_node Find(pugi::xml_node& startNode, const Tau::Strings& nodeNames);
    pugi::xml_node Find(const Tau::Strings& nodeNames);

    static std::string NodeToXmlString(const pugi::xml_node& node);
};