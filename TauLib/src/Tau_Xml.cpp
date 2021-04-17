#include "Tau_Xml.h"
#include <sstream>

using namespace pugi;
using namespace std;
using namespace Tau;

// loads the xml from a file and saves the filename in xmlFilePath
xml_parse_result Tau_Xml::Load(const string& filePath) {
    xml_parse_result result = load_file(filePath.c_str());
    if (result.status == status_ok)
        xmlFilePath = filePath;

    return result;
}

// saves the xml to xmlFilePath
bool Tau_Xml::Save() {
return SaveAs(xmlFilePath);
}

// saves the xml to passed filePath
bool Tau_Xml::SaveAs(const string& filePath) {
    return save_file(filePath.c_str());
}

// Clear all data
void Tau_Xml::Clear() {
    reset();
    xmlFilePath = "";
}

// add a tag/value pair in one call
xml_node Tau_Xml::AppendChild(xml_node& parent, const string& tagName, const string& value)
{
    if (parent) {
        xml_node node = parent.append_child(tagName.c_str());
        node.append_child(pugi::node_pcdata).set_value(value.c_str());
        return node;
    } else
        return xml_node();
}

// insert a tag/value pair before a child node in one call
xml_node Tau_Xml::InsertChildBefore(xml_node& parent, const string& tagName, const string& value, xml_node& beforeNode)
{
    if (parent && beforeNode) {
        xml_node node = parent.insert_child_before(tagName.c_str(), beforeNode);
        node.append_child(pugi::node_pcdata).set_value(value.c_str());
    } else
        return xml_node();

}

// insert a tag/value pair after a child node in one call
xml_node Tau_Xml::InsertChildAfter(xml_node& parent, const string& tagName, const string& value, xml_node& afterNode)
{
    if (parent && afterNode) {
        xml_node node = parent.insert_child_after(tagName.c_str(), afterNode);
        node.append_child(pugi::node_pcdata).set_value(value.c_str());
    } else
        return xml_node();

}

xml_node Tau_Xml::Find(xml_node& startNode, const Tau::Strings& nodeNames)
{
    if (startNode.empty())
        return xml_node();      // xml doc is empty, return empty node

    xml_node node = startNode;
    for (const string& name : nodeNames) {
        node = node.child(name.c_str());
        if (node.empty())
            return node;        // one of the node names is not found
    }

    return node;
}

// finds a node in the hierarchy starting from the root of the document.  returns an empty node if not found.
xml_node Tau_Xml::Find(const Strings& nodeNames) {
    return Find(*((xml_node*) (this)), nodeNames);
}

//
// GameXmlInfo::NodeToXmlString
//
string Tau_Xml::NodeToXmlString(const xml_node& node)
{
    stringstream str;
    node.print(str);

    return str.str();
}
