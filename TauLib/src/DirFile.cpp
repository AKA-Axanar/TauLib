#include "DirFile.h"
#include <string>
//#include <memory>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

///
/// @file
/// @brief cpp file for directory and file routines.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
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
string GetFileExtension(const string& str) {
    fs::path p(str);
    return p.extension().string();
}

//
// GetFileExtensionWithoutDot
// returns the file extension of the path without the leading ".".  ex: returns "dat" for "foo.dat"
//
string GetFileExtensionWithoutDot(const string& str) {
    string ext = GetFileExtension(str);
    if (ext.size() > 0 && ext[0] == '.')
        ext.erase(0, 1);
    return ext;
}

//
// GetFilename
// returns the filename in the path.  ex: returns "foo.dat" from "aaa/bbb/foo.dat"
//
string GetFilename(const string& str) {
    fs::path p(str);
    return p.filename().string();   
}

//
// returns the filename base/stem in the path.  ex: returns "foo" from "aaa/bbb/foo.dat"
// i.e. return the filename without the extension
string GetFilenameBase(const string& str) {
    fs::path p(str);
    return p.stem().string();   
}

//
// ReplaceFilename
// The modified path is returned.  the passed string is not modified.
//
string ReplaceFilename(const string& str, const string& new_filename) {
    fs::path p(str);
    return p.replace_filename(new_filename).string();   
}

//
// ReplaceFilename
// The passed path string is modified.  
//
void ReplaceFilename(string* str, const string& new_filename) {
    fs::path p(*str);
    *str = p.replace_filename(new_filename).string();   
}

//
// Replace File Extension.  either including or not including a "." work.
//
string ReplaceFileExtension(const string& str, const string& new_extension) {
    fs::path p(str);
    return p.replace_extension(new_extension).string();   
}
void ReplaceFileExtension(string* str, const string& new_extension) {
    fs::path p(*str);
    *str = p.replace_extension(new_extension).string();   
}

//
// Remove FilenameFromPath.  the "/" or "\" is at the end of the path.
// GetParentPath() is similar but does not have a "/" or "\" at the end.
//
string RemoveFilenameFromPath(const string& filePath) {
    fs::path p(filePath);
    return p.remove_filename().string();   
}
void RemoveFilenameFromPath(string* filePath) {
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
string GetParentPath(const string& str) {
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
bool CreateDirPath(const string& str) {
    return fs::create_directories(str);
}

//
// does file or directory exist
//
bool FileExists(const string& filePath) {
    return fs::exists(filePath) && fs::is_regular_file(filePath);
}
bool DirExists(const string& dirPath) {
    return fs::exists(dirPath) && fs::is_directory(dirPath);
}


//
// get file size
//
uintmax_t GetFileSize(const string& filePath) {
    return fs::file_size(filePath);
}

//
// delete file or directory
//
bool DeleteFile(const string& filePath) {
    return FileExists(filePath) && fs::remove(filePath);
}
bool DeleteDirectory(const string& dirPath) {
    return DirExists(dirPath) && fs::remove_all(dirPath);
}

//
// rename file or directory (recursive)
//
bool RenameFile(const string& filePathFrom, const string& filePathTo) {
    if (!FileExists(filePathFrom))
        return false;           // the file doesn't exist
    if (FileExists(filePathTo))
        return false;           // to file name exists.  delete it first.

    fs::rename(filePathFrom, filePathTo);
    return true;
}
// this is recursive
bool RenameDir(const string& dirPathFrom, const string& dirPathTo) {
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
bool CopyFileOverwrite(const string& filePathSrc, const string& filePathDest) {
    return fs::copy_file(filePathSrc, filePathDest, fs::copy_options::overwrite_existing);
}
bool CopyFileSkipExisting(const string& filePathSrc, const string& filePathDest) {
    return fs::copy_file(filePathSrc, filePathDest, fs::copy_options::skip_existing);
}

//
// copy directories (recursive)
//
bool CopyDirOverwrite(const string& dirPathSrc, const string& dirPathDest) {
    if (!DirExists(dirPathSrc))
        return false;

    fs::copy(dirPathSrc, dirPathDest, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
    return true;
}
bool CopyDirSkipExisting(const string& dirPathSrc, const string& dirPathDest) {
    if (!DirExists(dirPathSrc))
        return false;

    fs::copy(dirPathSrc, dirPathDest, fs::copy_options::recursive | fs::copy_options::skip_existing);
    return true;
}

                //*******************************
                // Temp Directory and Temp File
                //*******************************
//
// Returns an existing directory where you can create temporary files.  
// Do NOT delete this directory, but create temporary files and dirs inside it.
// 
string GetTempDir() {
    string tempDirPath = filesystem::temp_directory_path().string();
    return tempDirPath;
}

//
// Get the full path of a unique filename you can use for creating a temporary file or dir.
//
string GetATempFilename() {
    char buf[L_tmpnam_s];
    int ret = tmpnam_s(buf, L_tmpnam_s);    // ret == 0 on success
    if (ret == 0)
        return buf;
    else
        return "";
}

} // end namespace Tau