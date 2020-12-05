#pragma once
#include <string>
#include "TauLib.h"

/**
 *  @file
 *
 *  Header file for directory and file routines.
 *
 */

/**
 *  \brief avoid conflict with other libraries
 */
namespace Tau {

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

                //*******************************
                // Directories and Files
                //*******************************

//
// get the current directory (pwd)
//
std::string GetCurrentDirPath();

//
// Create a Directory path.  
// CreateDirectory("aaa/bbb/ccc") will also create the directories aaa and aaa/bbb if they don't already exist.
//
bool CreateDirPath(const std::string& dirPath);

//
// does file or directory exist
//
bool FileExists(const std::string& filePath);
bool DirExists(const std::string& dirPath);

//
// get file size
//
uintmax_t GetFileSize(const std::string& filePath);

//
// delete file or directory
//
bool DeleteFile(const std::string& filePath);
bool DeleteDirectory(const std::string& dirPath);   // this is recursive

//
// rename file or directory
//
bool RenameFile(const std::string& filePathFrom, const std::string& filePathTo);
bool RenameDir(const std::string& dirPathFrom, const std::string& dirPathTo);

//
// copy file
//
bool CopyFileOverwrite(const std::string& filePathSrc, const std::string& filePathDest);
bool CopyFileSkipExisting(const std::string& filePathSrc, const std::string& filePathDest);

//
// copy directories (recursive)
//
bool CopyDirOverwrite(const std::string& dirPathSrc, const std::string& dirPathDest);
bool CopyDirSkipExisting(const std::string& dirPathSrc, const std::string& dirPathDest);

} // end namespace Tau
