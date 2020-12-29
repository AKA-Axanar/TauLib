#pragma once
#include <string>
#include "TauLib.h"
#include "Str.h"

///
/// @file
/// @brief Header file for directory and file routines.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///

///
/// @brief namespace Tau - avoid conflict with other libraries
///
namespace Tau {

                //*******************************
                // Filenames
                //*******************************

///
/// @brief GetFileExtension
/// @param str the file path
/// @return the file extension of the path.  ex: returns ".dat" from "foo.dat"
/// @remark Note: the returned file extension includes the "."
///
    std::string GetFileExtension(const std::string& str);

///
/// @brief GetFileExtensionWithoutDot
/// @param str the file path
/// @return the file extension of the path wiithout the leading period.  ex: returns "dat" from "foo.dat"
///
std::string GetFileExtensionWithoutDot(const std::string& str);

///
/// @brief GetFilename
/// @param str the file path
/// @return the filename in the path.  ex: returns "foo.dat" from "aaa/bbb/foo.dat"
///
std::string GetFilename(const std::string& str);

///
/// @brief GetFilenameBase
/// @param str the file path
/// @return the filename base/stem in the path.  ex: returns "foo" from "aaa/bbb/foo.dat"
///
std::string GetFilenameBase(const std::string& str);

//
// @brief ReplaceFilename
/// @param str the file path
/// @param new_filename the new filename
/// @remark ReplaceFilename("aaa/bbb/foo.dat", "bar.txt) results in "aaa/bbb/bar.txt"
/// @return The modified path.  the passed string is not modified.
///
std::string ReplaceFilename(const std::string& str, const std::string& new_filename);

///
// @brief ReplaceFilename
/// @param str the file path
/// @param new_filename the new filename
/// @remark ReplaceFilename("aaa/bbb/foo.dat", "bar.txt) results in "aaa/bbb/bar.txt"
/// @return none
///
void ReplaceFilename(std::string* str, const std::string& new_filename);

///
/// @brief ReplaceFileExtension
/// @param str the file path
/// @param new_extension the new file extension
/// @remark Either including or not including a "." works.
/// @return The modified path.  the passed string is not modified.
///
std::string ReplaceFileExtension(const std::string& str, const std::string& new_extension);

///
/// @brief ReplaceFileExtension
/// @param str the file path
/// @param new_extension the new file extension
/// @remark Either including or not including a "." works.  The passed filepath is modified.
/// @return none
///
void ReplaceFileExtension(std::string* str, const std::string& new_extension);

///
/// @brief RemoveFilenameFromPath
/// @remark Remove the Filename pportion from the path.  the "/" or "\" is at the end of the path.
/// @remark GetParentPath() is similar but does not have a "/" or "\" at the end.
/// @param filePath the path string that includes a filename
/// @return the path string with the filename removed.  The passed string is not modified
///
std::string RemoveFilenameFromPath(const std::string& filePath);

///
/// @brief RemoveFilenameFromPath
/// @remark Remove the Filename pportion from the path.  the "/" or "\" is at the end of the path.
/// @remark GetParentPath() is similar but does not have a "/" or "\" at the end.
/// @param filePath the path string that includes a filename
/// @return none. The filename postion of the filePath is removed from the passed string
///
void RemoveFilenameFromPath(std::string* filePath);

                //*******************************
                // Paths
                //*******************************

///
/// @brief GetParentPath
/// @param str the file path
/// @return the parent path.  ex: returns "aaa/bbb" for "aaa/bbb/foo.dat"
///                           ex: returns "aaa" for "aaa/bbb"
///
std::string GetParentPath(const std::string& str);

                //*******************************
                // Directories and Files
                //*******************************

///
/// @brief GetCurrentDirPath
/// @return the current directory (pwd)
///
std::string GetCurrentDirPath();

///
/// @brief CreateDirPath Create a Directory path.
/// @param dirPath the directory path to create
/// @remark CreateDirectory("aaa/bbb/ccc") will also create the directories aaa and aaa/bbb if they don't already exist.
/// @return bool true if successfull
///
bool CreateDirPath(const std::string& dirPath);

///
/// @brief FileExists Does the file exist?
/// @param filePath the file path
/// @return true if it exists
///
bool FileExists(const std::string& filePath);

///
/// @brief DirExists Does the directory exist?
/// @param dirPath the directory path
/// @return true if it exists
///
bool DirExists(const std::string& dirPath);

///
/// @brief GetFileSize get the file size
/// @param filePath the file path
/// @return the size of the file
/// 
uintmax_t GetFileSize(const std::string& filePath);

///
/// @brief DeleteFile
/// @param filePath the file path
/// @return true if the file was deleted
///
bool DeleteFile(const std::string& filePath);

///
/// @brief DeleteDirectory
/// @param dirPath the directory path
/// @return true if the directory and it's subdirectories were deleted
///
bool DeleteDirectory(const std::string& dirPath);   // this is recursive

///
/// @brief RenameFile
/// @param filePathFrom the file to be renamed
/// @param filePathTo the new filename
/// @return true if the file was renamed
///
bool RenameFile(const std::string& filePathFrom, const std::string& filePathTo);

///
/// @brief RenameDir
/// @param dirPathFrom the directory to be renamed
/// @param dirPathTo the new directory name
/// @return true if the directory was renamed
///
bool RenameDir(const std::string& dirPathFrom, const std::string& dirPathTo);

///
/// @brief CopyFileOverwrite
/// @param filePathSrc the file being copied
/// @param filePathDest the file it's being copied to
/// @remark if the destination file already exists, it is overwritten
/// @return true if successful
/// 
bool CopyFileOverwrite(const std::string& filePathSrc, const std::string& filePathDest);

///
/// @brief CopyFileSkipExisting
/// @param filePathSrc the file being copied
/// @param filePathDest the file it's being copied to
/// @remark if the destination file already exists, the copy is skipped
/// @return true if successful
/// 
bool CopyFileSkipExisting(const std::string& filePathSrc, const std::string& filePathDest);

///
/// @brief CopyDirOverwrite
/// @param dirPathSrc the file being copied
/// @param dirPathDest the file it's being copied to
/// @remark if the destination file already exists, the copy is overwritten
/// @return true if successful
/// 
bool CopyDirOverwrite(const std::string& dirPathSrc, const std::string& dirPathDest);

///
/// @brief CopyDirOverwrite
/// @param dirPathSrc the file being copied
/// @param dirPathDest the file it's being copied to
/// @remark if the destination file already exists, the copy is skipped
/// @return true if successful
/// 
bool CopyDirSkipExisting(const std::string& dirPathSrc, const std::string& dirPathDest);

                //*******************************
                // Temp Directory and Temp File
                //*******************************

///
/// @brief Get an existing directory where you can create temporary files.  
/// @param none
/// @return An existing directory where you can create temporary files.  
/// Do NOT delete this directory, but create temporary files and dirs inside it.
/// 
std::string GetTempDir();

///
/// @brief Get a full path filename for creating a temporary file.
/// @param none
/// @return The full path of a unique filename you can use for creating a temporary file or dir.
///
std::string GetATempFilename();

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
Strings ReadTextFileAsAStringArray(const std::string& filePath, bool removeCRLF);

                //*******************************
                // Compare Text Files
                //*******************************

/// @brief CompareFiles
/// @param filePath1 fullpath to file1
/// @param filePath2 fullpath to file2
/// @param ignoreCRLF true to ignore CR/LF's when comparing
/// @return true if the file strings are the same (considering ignoreCRLF flag)
bool CompareFiles(const std::string& filePath1, const std::string& filePath2, bool ignoreCRLF=false);

} // end namespace Tau
