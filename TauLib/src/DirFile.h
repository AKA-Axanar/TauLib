#pragma once
#include <string>
#include "TauLib.h"

namespace Tau { // too avoid conflict with other libraries

                //*******************************
                // Filenames
                //*******************************

//
// returns the file extension of the path.  ex: returns ".dat" from "foo.dat"
// the return includes the "."
//
    std::string GetFileExtension(const std::string& str);

//
// returns the file extension of the path without the leading ".".  ex: returns "dat" from "foo.dat"
//
std::string GetFileExtensionWithoutDot(const std::string& str);

//
// returns the filename in the path.  ex: returns "foo.dat" from "aaa/bbb/foo.dat"
//
std::string GetFilename(const std::string& str);

//
// returns the filename base/stem in the path.  ex: returns "foo" from "aaa/bbb/foo.dat"
// i.e. return the filename without the extension
std::string GetFilenameBase(const std::string& str);

//
// Replace Filename
//
std::string ReplaceFilename(const std::string& str, const std::string& new_filename);
void ReplaceFilename(std::string* str, const std::string& new_filename);

//
// Replace File Extension.  either including or not including a "." work.
//
std::string ReplaceFileExtension(const std::string& str, const std::string& new_extension);
void ReplaceFileExtension(std::string* str, const std::string& new_extension);

//
// Remove Filename.  the "/" or "\" is at the end of the path.
// GetParentPath() is similar but does not have a "/" or "\" at the end.
//
std::string RemoveFilename(const std::string& str);
void RemoveFilename(std::string* str);

                //*******************************
                // Paths
                //*******************************

//
// returns the parent path.  ex: returns "aaa/bbb" from "aaa/bbb/foo.dat"
//                           ex: returns "aaa" from "aaa/bbb"
//
std::string GetParentPath(const std::string& str);

}
