#include "DirFile.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <assert.h>

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
// GetFileExtensionWithDot
// returns the file extension of the path.  ex: returns ".dat" for "foo.dat"
// the return includes the file extension "."
//
string GetFileExtensionWithDot(const string& str) {
    fs::path p(str);
    return p.extension().string();
}

//
// GetFileExtensionWithoutDot
// returns the file extension of the path without the leading ".".  ex: returns "dat" for "foo.dat"
//
string GetFileExtensionWithoutDot(const string& str) {
    string ext = GetFileExtensionWithDot(str);
    if (ext.size() > 0 && ext[0] == '.')
        ext.erase(0, 1);
    return ext;
}

//
// GetFilename
// returns the filename in the path.  ex: returns "foo.dat" from "aaa/bbb/foo.dat"
// If the path is a directory it returns the last part of the dir path.  ex: returns "ccc" from "aaa/bbb/ccc"
//
string GetFilename(const string& str) {
    fs::path p(str);
    return p.filename().string();   
}

//
// returns the base/stem of the filename.  ex: returns "foo" from "aaa/bbb/foo.dat".  i.e. return the filename without the extension
// If the path is a directory it returns the last part of the dir path.  ex: returns "ccc" from "aaa/bbb/ccc"

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
//
// Replace File Extension.  either including or not including a "." work.
// The passed path string is modified.  
//
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

///
/// set the current disrectory
///
void SetCurrentDirPath(const std::string& dirpath) {
    fs::current_path(dirpath);
}

//
// Create a Directory path.  
// CreateDir("aaa/bbb/ccc") will also create the directires aaa and aaa/bbb if they don't already exist.
//
bool CreateDir(const string& str) {
    error_code ec;
    fs::create_directories(str, ec);
    return !ec;     // return true if successful
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
    if (FileExists(filePath))
        return fs::file_size(filePath);
    else
        return 0;
}

//
// delete file or directory
//
bool DeleteFile(const string& filePath) {
    return FileExists(filePath) && fs::remove(filePath);
}
bool DeleteDir(const string& dirPath) {
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

    error_code ec;
    fs::rename(filePathFrom, filePathTo, ec);
    return !ec;     // return true if successful
}
// this is recursive
bool RenameDir(const string& dirPathFrom, const string& dirPathTo) {
    if (!DirExists(dirPathFrom))
        return false;           // the dir doesn't exist
    if (DirExists(dirPathTo))
        return false;           // to dir name exists.  delete it first.

    error_code ec;
    fs::rename(dirPathFrom, dirPathTo, ec);
    return !ec;     // return true if successful
}

//
// copy file
//
bool CopyFile(const string& filePathSrc, const string& filePathDest) {
    error_code ec;
    fs::copy_file(filePathSrc, filePathDest, fs::copy_options::overwrite_existing, ec);
    return !ec;     // return true if successful
}

//
// copy file skip existing files
//
bool CopyFile_SkipExisting(const string& filePathSrc, const string& filePathDest) {
    error_code ec;
    fs::copy_file(filePathSrc, filePathDest, fs::copy_options::skip_existing, ec);
    return !ec;     // return true if successful
}

//
// copy directories (recursive)
//
bool CopyDir(const string& dirPathSrc, const string& dirPathDest) {
    if (!DirExists(dirPathSrc))
        return false;

    error_code ec;
    fs::copy(dirPathSrc, dirPathDest, fs::copy_options::recursive | fs::copy_options::overwrite_existing, ec);
    return !ec;     // return true if successful
}

//
// copy directories (recursive) skip existing files
//
bool CopyDir_SkipExisting(const string& dirPathSrc, const string& dirPathDest) {
    if (!DirExists(dirPathSrc))
        return false;

    error_code ec;
    fs::copy(dirPathSrc, dirPathDest, fs::copy_options::recursive | fs::copy_options::skip_existing, ec);
    return !ec;     // return true if successful
}

                //*******************************
                // Get list of files and directories
                //*******************************

//
// return directory contents as strings of file or dir names
// takes lambdas to control what gets returned
//
Strings GetDirectoryContents(const string& dirPath, 
                             function<bool (fs::directory_entry&)> testLambda,
                             function<string (fs::directory_entry&)> getStringLambda,
                             bool recursive
                             )
{
    Strings result;
    if (!DirExists(dirPath))
        return result;

    if (recursive) {
        for (auto dir_entry : fs::recursive_directory_iterator(dirPath)) {
            if (testLambda(dir_entry)) {
                result.emplace_back(getStringLambda(dir_entry));
            }
        }
    } else {
        for (auto dir_entry : fs::directory_iterator(dirPath)) {
            if (testLambda(dir_entry)) {
                result.emplace_back(getStringLambda(dir_entry));
            }
        }
    }

    return result;
}

//
// 
//
Strings GetFileNamesInDir(const std::string& dirPath)
    { return GetDirectoryContents(dirPath, is_file, get_name); }

//
// GetFileFullPathsInDir
//
Strings GetFileFullPathsInDir(const std::string& dirPath)
    { return GetDirectoryContents(dirPath, is_file, get_fullpath); }

//
// GetDirNamesInDir
//
Strings GetDirNamesInDir(const std::string& dirPath)
    { return GetDirectoryContents(dirPath, is_directory, get_name); }

//
// GetDirFullPathsInDir
//
Strings GetDirFullPathsInDir(const std::string& dirPath)
    { return GetDirectoryContents(dirPath, is_directory, get_fullpath); }

//
// GetFileFullPathsInDir_Recursive
//
Strings GetFileFullPathsInDir_Recursive(const std::string& dirPath)
    { return GetDirectoryContents(dirPath, is_file, get_fullpath, true); }

//
// GetDirFullPathsInDir_Recursive
//
Strings GetDirFullPathsInDir_Recursive(const std::string& dirPath)
    { return GetDirectoryContents(dirPath, is_directory, get_fullpath, true); }

//
// GetFileNamesWithExtInDir
//
Strings GetFileNamesWithExtInDir(const std::string& dirPath, std::string ext) {
    // if no '.' in the front of the extension, add one.
    if (ext.size() == 0 || ext[0] != '.')
        ext.insert(ext.begin(), '.');
    auto is_file_with_ext = [&] (fs::directory_entry& entry)->bool { return entry.is_regular_file() && icompareBool(entry.path().extension().string(), ext); };
    return GetDirectoryContents(dirPath, is_file_with_ext, get_name);
}

//
// GetFileNamesWithTheseExtInDir
//
Strings GetFileNamesWithTheseExtInDir(const std::string& dirPath, Strings extensions) {
    Strings filenames;
    for (const auto& ext : extensions) {
        Strings more = GetFileNamesWithExtInDir(dirPath, ext);
        filenames.insert(filenames.end(), more.begin(), more.end());
    }

    return filenames;
}

//
// GetFileFullPathsWithExtInDir_Recursive
//
Strings GetFileFullPathsWithExtInDir_Recursive(const std::string& dirPath, std::string ext) {
    // if no '.' in the front of the extension, add one.
    if (ext.size() == 0 || ext[0] != '.')
        ext.insert(ext.begin(), '.');
    auto is_file_with_ext = [&] (fs::directory_entry& entry)->bool { return entry.is_regular_file() && icompareBool(entry.path().extension().string(), ext); };
    return GetDirectoryContents(dirPath, is_file_with_ext, get_fullpath, true);
}

//
// GetFileFullPathsWitThesehExtInDir_Recursive
//
Strings GetFileFullPathsWithTheseExtInDir_Recursive(const std::string& dirPath, Strings extensions) {
    Strings filenames;
    for (const auto& ext : extensions) {
        Strings more = GetFileFullPathsWithExtInDir_Recursive(dirPath, ext);
        filenames.insert(filenames.end(), more.begin(), more.end());
    }

    return filenames;
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

                //*******************************
                // Read File
                //*******************************
///
/// @brief Return the contents of a text file in a vector of string.
/// @param filePath The File to read.
/// @param removeCRLF Wether to remove any CR or LF's fromt he strings.
/// @return A vector<string> containing the contents of the file (optionally minus any CR or LF's).
/// @note CR's and LF's are removed.
/// 
Strings ReadTextFileAsAStringArray(const string& filePath, bool removeCRLF) {
    ifstream file;
    string line;
    Strings contents;

    file.open(filePath);
    if (!file.good()) {
        cout << "Error opening file: " << filePath << endl;
        return contents;
    }

    while (getline(file, line)) {
        if (removeCRLF)
            RemoveCRLFCharsFromEndOfString(&line);

        contents.emplace_back(line);
    };
    file.close();

    return contents;
}

                //*******************************
                // Compare Text Files
                //*******************************

/// @brief CompareFiles
/// @param filePath1 fullpath to file1
/// @param filePath2 fullpath to file2
/// @param ignoreCRLF true to ignore CR/LF's when comparing
/// @return true if the file strings are the same (considering ignoreCRLF flag)
bool CompareFiles(const string& filePath1, const string& filePath2, bool ignoreCRLF) {
    Strings file1 = ReadTextFileAsAStringArray(filePath1, ignoreCRLF);
    Strings file2 = ReadTextFileAsAStringArray(filePath2, ignoreCRLF);

    if (file1.size() != file2.size())
        return false;   // different file size

    for (int i=0; i < file1.size(); ++i) {
        auto a = file1[i];
        auto b = file2[i];
        if (file1[i] != file2[i]) {
            cout << '"' << file1[i] << '"' << endl;
            cout << '"' << file2[i] << '"' << endl;
            return false;   // different content
        }
    }

    return true;    // files are equal
}

                //*******************************
                // Space Available
                //*******************************

/// @brief SpaceAvailable
/// @param A path on the drive you want the free space available
/// @return Disk space available on the drive the passed path is on
uintmax_t SpaceAvailable(const string& fileOrDirPath) {
    return fs::space(fileOrDirPath).available;
}

} // end namespace Tau