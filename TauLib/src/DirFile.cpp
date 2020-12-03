#include "DirFile.h"
#include <string>
//#include <memory>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

namespace Tau { // too avoid conflict with other libraries

                //*******************************
                // Filenames
                //*******************************

//
// returns the file extension of the path.  ex: returns ".dat" for "foo.dat"
// the return includes the "."
//
std::string GetFileExtension(const std::string& str) {
    fs::path p(str);
    return p.extension().string();
}

//
// returns the file extension of the path without the leading ".".  ex: returns "dat" for "foo.dat"
//
std::string GetFileExtensionWithoutDot(const std::string& str) {
    string ext = GetFileExtension(str);
    if (ext.size() > 0 && ext[0] == '.')
        ext.erase(0, 1);
    return ext;
}

//
// returns the filename in the path.  ex: returns "foo.dat" from "aaa/bbb/foo.dat"
//
std::string GetFilename(const std::string& str) {
    fs::path p(str);
    return p.filename().string();   
}

//
// returns the filename base/stem in the path.  ex: returns "foo" from "aaa/bbb/foo.dat"
// i.e. return the filename without the extension
std::string GetFilenameBase(const std::string& str) {
    fs::path p(str);
    return p.stem().string();   
}

//
// Replace Filename
//
std::string ReplaceFilename(const std::string& str, const std::string& new_filename) {
    fs::path p(str);
    return p.replace_filename(new_filename).string();   
}
void ReplaceFilename(std::string* str, const std::string& new_filename) {
    fs::path p(*str);
    *str = p.replace_filename(new_filename).string();   
}

//
// Replace File Extension.  either including or not including a "." work.
//
std::string ReplaceFileExtension(const std::string& str, const std::string& new_extension) {
    fs::path p(str);
    return p.replace_extension(new_extension).string();   
}
void ReplaceFileExtension(std::string* str, const std::string& new_extension) {
    fs::path p(*str);
    *str = p.replace_extension(new_extension).string();   
}

//
// Remove Filename.  the "/" or "\" is at the end of the path.
// GetParentPath() is similar but does not have a "/" or "\" at the end.
//
std::string RemoveFilename(const std::string& str) {
    fs::path p(str);
    return p.remove_filename().string();   
}
void RemoveFilename(std::string* str) {
    fs::path p(*str);
    *str =  p.remove_filename().string();   
}

                //*******************************
                // Paths
                //*******************************

//
// returns the parent path.  ex: returns "aaa/bbb" from "aaa/bbb/foo.dat"
//                           ex: returns "aaa" from "aaa/bbb"
//
std::string GetParentPath(const std::string& str) {
    fs::path p(str);
    return p.parent_path().string();   
}

}