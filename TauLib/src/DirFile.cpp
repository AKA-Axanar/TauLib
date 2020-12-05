#include "DirFile.h"
#include <string>
//#include <memory>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

///
/// @file
/// CPP file for directory and file routines.
///

namespace Tau {  // to avoid conflict with other libraries

                //*******************************
                // Filenames
                //*******************************

//
// GetFileExtension
// returns the file extension of the path.  ex: returns ".dat" for "foo.dat"
// the return includes the file extension "."
//
std::string GetFileExtension(const std::string& str) {
    fs::path p(str);
    return p.extension().string();
}

//
// GetFileExtensionWithoutDot
// returns the file extension of the path without the leading ".".  ex: returns "dat" for "foo.dat"
//
std::string GetFileExtensionWithoutDot(const std::string& str) {
    string ext = GetFileExtension(str);
    if (ext.size() > 0 && ext[0] == '.')
        ext.erase(0, 1);
    return ext;
}

//
// GetFilename
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
// ReplaceFilename
// The modified path is returned.  the passed string is not modified.
//
std::string ReplaceFilename(const std::string& str, const std::string& new_filename) {
    fs::path p(str);
    return p.replace_filename(new_filename).string();   
}

//
// ReplaceFilename
// The passed path string is modified.  
//
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
// Remove FilenameFromPath.  the "/" or "\" is at the end of the path.
// GetParentPath() is similar but does not have a "/" or "\" at the end.
//
std::string RemoveFilenameFromPath(const std::string& filePath) {
    fs::path p(filePath);
    return p.remove_filename().string();   
}
void RemoveFilenameFromPath(std::string* filePath) {
    fs::path p(*filePath);
    *filePath =  p.remove_filename().string();   
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

                //*******************************
                // Directories and Files
                //*******************************

//
// get the current directory (pwd)
//
string GetCurrentDirPath() {
    return fs::current_path().string();
}

//
// Create a Directory path.  
// CreateDirectory("aaa/bbb/ccc") will also create the directires aaa and aaa/bbb if they don't already exist.
//
bool CreateDirPath(const std::string& str) {
    return fs::create_directories(str);
}

//
// does file or directory exist
//
bool FileExists(const std::string& filePath) {
    return fs::exists(filePath) && fs::is_regular_file(filePath);
}
bool DirExists(const std::string& dirPath) {
    return fs::exists(dirPath) && fs::is_directory(dirPath);
}


//
// get file size
//
uintmax_t GetFileSize(const std::string& filePath) {
    return fs::file_size(filePath);
}

//
// delete file or directory
//
bool DeleteFile(const std::string& filePath) {
    return FileExists(filePath) && fs::remove(filePath);
}
bool DeleteDirectory(const std::string& dirPath) {
    return DirExists(dirPath) && fs::remove_all(dirPath);
}

//
// rename file or directory (recursive)
//
bool RenameFile(const std::string& filePathFrom, const std::string& filePathTo) {
    if (!FileExists(filePathFrom))
        return false;           // the file doesn't exist
    if (FileExists(filePathTo))
        return false;           // to file name exists.  delete it first.

    fs::rename(filePathFrom, filePathTo);
    return true;
}
// this is recursive
bool RenameDir(const std::string& dirPathFrom, const std::string& dirPathTo) {
    if (!DirExists(dirPathFrom))
        return false;           // the dir doesn't exist
    if (DirExists(dirPathTo))
        return false;           // to dir name exists.  delete it first.

    fs::rename(dirPathFrom, dirPathTo);
    return true;
}

//
// copy file
//
bool CopyFileOverwrite(const std::string& filePathSrc, const std::string& filePathDest) {
    return fs::copy_file(filePathSrc, filePathDest, fs::copy_options::overwrite_existing);
}
bool CopyFileSkipExisting(const std::string& filePathSrc, const std::string& filePathDest) {
    return fs::copy_file(filePathSrc, filePathDest, fs::copy_options::skip_existing);
}

//
// copy directories (recursive)
//
bool CopyDirOverwrite(const std::string& dirPathSrc, const std::string& dirPathDest) {
    if (!DirExists(dirPathSrc))
        return false;

    fs::copy(dirPathSrc, dirPathDest, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
    return true;
}
bool CopyDirSkipExisting(const std::string& dirPathSrc, const std::string& dirPathDest) {
    if (!DirExists(dirPathSrc))
        return false;

    fs::copy(dirPathSrc, dirPathDest, fs::copy_options::recursive | fs::copy_options::skip_existing);
    return true;
}

} // end namespace Tau