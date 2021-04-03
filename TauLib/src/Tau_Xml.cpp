#include "Tau_Xml.h"

using namespace pugi;
using namespace std;
//using namespace Tau;

// loads the xml from a file and saves the filename in xmlFilePath
xml_parse_result Tau_Xml::Load(const std::string& filePath) {
    xml_parse_result result = xml_document::load_file(filePath.c_str());
    if (result.status == status_ok)
        xmlFilePath = filePath;

    return result;
}

// saves the xml to xmlFilePath
bool Tau_Xml::Save() {
return true;
}

// saves the xml to passed filePath
bool Tau_Xml::SaveAs(const std::string& filePath) {
return true;
}

// Clear all data
void Tau_Xml::Clear() {
    xml_document::reset();
    xmlFilePath = "";
}

// finds a node in the hierarchy starting from the root of the document.  returns an empty node if not found.
xml_node Tau_Xml::Find(const Tau::Strings& nodeNames) {
    if (empty())
        return xml_node();      // xml doc is empty, return empty node

    xml_node node = *((xml_node*) (this));
    for (const string& name : nodeNames) {
        node = node.child(name.c_str());
        if (node.empty())
            return node;        // one of the node names is not found
    }

    return node;
}
