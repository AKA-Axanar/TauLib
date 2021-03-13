#pragma once
#include <string>
#include "TauLib.h"
#include "Str.h"
#include <filesystem>
#include <functional>

namespace fs = std::filesystem;

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
/// @brief GetFileExtensionWithDot
/// @param str the file path
/// @return the file extension of the path.  ex: returns ".dat" from "foo.dat"
/// @remark Note: the returned file extension includes the "."
///
    std::string GetFileExtensionWithDot(const std::string& str);

///
/// @brief GetFileExtensionWithoutDot
/// @param str the file path
/// @return the file extension of the path wiithout the leading period.  ex: returns "dat" from "foo.dat"
///
std::string GetFileExtensionWithoutDot(const std::string& str);

///
/// @brief GetFilename
/// @param str the file path
/// @return the filename in the path.  ex: returns "foo.dat" from "aaa/bbb/foo.dat".  
/// @return If the path is a directory it returns the last part of the dir path.  ex: returns "ccc" from "aaa/bbb/ccc"
///
std::string GetFilename(const std::string& str);

///
/// @brief GetFilenameBase
/// @param str the file path
/// @return If the path ends in a filename it returns the filename base/stem of the filename.  ex: returns "foo" from "aaa/bbb/foo.dat"
/// @return If the path is a directory it returns the last part of the dir path.  ex: returns "ccc" from "aaa/bbb/ccc"
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
/// @brief SetCurrentDirPath
///
void SetCurrentDirPath(const std::string& dirpath);

///
/// @brief CreateDir Create a Directory path.
/// @param dirPath the directory path to create
/// @remark CreateDirectory("aaa/bbb/ccc") will also create the directories aaa and aaa/bbb if they don't already exist.
/// @return bool true if successfull
///
bool CreateDir(const std::string& dirPath);

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
/// @brief DeleteDir
/// @param dirPath the directory path
/// @return true if the directory and it's subdirectories were deleted
///
bool DeleteDir(const std::string& dirPath);   // this is recursive

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
/// @brief CopyFile
/// @param filePathSrc the file being copied
/// @param filePathDest the file it's being copied to
/// @remark if the destination file already exists, it is overwritten
/// @return true if successful
/// 
bool CopyFile(const std::string& filePathSrc, const std::string& filePathDest);

///
/// @brief CopyFile_SkipExisting
/// @param filePathSrc the file being copied
/// @param filePathDest the file it's being copied to
/// @remark if the destination file already exists, the copy is skipped
/// @return true if successful
/// 
bool CopyFile_SkipExisting(const std::string& filePathSrc, const std::string& filePathDest);

///
/// @brief CopyDir
/// @param dirPathSrc the file being copied
/// @param dirPathDest the file it's being copied to
/// @remark if the destination file already exists, the copy is overwritten
/// @return true if successful
/// 
bool CopyDir(const std::string& dirPathSrc, const std::string& dirPathDest);

///
/// @brief CopyDir_SkipExisting
/// @param dirPathSrc the file being copied
/// @param dirPathDest the file it's being copied to
/// @remark if the destination file already exists, the copy is skipped
/// @return true if successful
/// 
bool CopyDir_SkipExisting(const std::string& dirPathSrc, const std::string& dirPathDest);

                //*******************************
                // Get list of files and directories
                //*******************************

// Add new lambdas as needed

/// @brief lambda to return if a directory_entry is a file
inline auto is_file =      [] (fs::directory_entry& entry)->bool { return entry.is_regular_file(); };
/// @brief lambda to return if a directory_entry is a directory
inline auto is_directory = [] (fs::directory_entry& entry)->bool { return entry.is_directory(); };

/// @brief lambda to return the file name or dir name portion of a directory_entry
inline auto get_name =     [] (fs::directory_entry& entry)->std::string { return entry.path().filename().string(); };
/// @brief lambda to return the ful path of a file name or dir name of a directory_entry
inline auto get_fullpath = [] (fs::directory_entry& entry)->std::string { return entry.path().string(); };

/// @brief return directory contents as strings of file or dir names
/// @param dirPath The directory path to open
/// @param testLambda A lambda function that tests the directory_entry as to whether to include the entry or not.
/// @param getStringLambda What string you wish to return from the entry if it passed your test.
/// @param recursive True to recursively read the entire directory hierarchy.
/// @return A vector of strings of file names, dir names, or full file/dir paths.
Strings GetDirectoryContents(const std::string& dirPath, 
                             std::function<bool (fs::directory_entry&)> testLambda,
                             std::function<std::string (fs::directory_entry&)> getStringLambda,
                             bool recursive = false
                             );

/// @brief GetFileNamesInDir Return the list of file names in a directory.
/// @param The directory path to open.
/// Ex: "aaa/bbb/foo.dat". if passed "aaa/bbb", "foo.dat" would be one of the file names returned.
/// @return A vector of strings containing file names.
/// 
Strings GetFileNamesInDir(const std::string& dirPath);

/// @brief GetFileFullPathsInDir Return the list of file name full paths in a directory.
/// @param The directory path to open.
/// Ex: "aaa/bbb/foo.dat". if passed "aaa/bbb", "aaa/bbb/foo.dat" would be one of the file name full paths returned.
/// @return A vector of strings containing file name full paths.
/// 
Strings GetFileFullPathsInDir(const std::string& dirPath);

/// @brief GetDirNamesInDir Return the list of directory names in a directory.
/// @param The directory path to open.
/// Ex: "aaa/bbb/ccc/foo.dat". if passed "aaa/bbb", "ccc" would be one of the directory names returned.
/// @return A vector of strings containing directory names.
/// 
Strings GetDirNamesInDir(const std::string& dirPath);

/// @brief GetDirFullPathsInDir Return the list of directory names in a directory.
/// @param The directory path to open.
/// Ex: "aaa/bbb/ccc/foo.dat". if passed "aaa/bbb", "aaa/bbb/ccc" would be one of the directory paths returned.
/// @return A vector of strings containing directory names.
/// 
Strings GetDirFullPathsInDir(const std::string& dirPath);

/// @brief GetFileFullPathsInDir_Recursive Return the list of file name full paths in a directory.
/// Same as GetFileFullPathsInDir but it continues through the entire sub-directory hierarchy.
/// @param The directory path to open.
/// @return A vector of strings containing file name full paths.
/// 
Strings GetFileFullPathsInDir_Recursive(const std::string& dirPath);

/// @brief GetDirFullPathsInDir_Recursive Return the list of directory names in a dir.
/// Same as GetDirFullPathsInDir but it continues through the entire sub-directory hierarchy.
/// @param The directory path to open.
/// Ex: "aaa/bbb/ccc/foo.dat". if passed "aaa/bbb", "aaa/bbb/ccc" would be one of the directory paths returned.
/// @return A vector of strings containing directory paths.
/// 
Strings GetDirFullPathsInDir_Recursive(const std::string& dirPath);

/// @brief GetFileNamesWithExtInDir Return the list of file names in a directory that have a particular extension.
/// @param The directory path to open.
/// @return A vector of strings containing file names with that file extension.
/// @note The file extension is compared case insensitive.
Strings GetFileNamesWithExtInDir(const std::string& dirPath, std::string ext);

/// @brief GetFileNamesWithTheseExtInDir Return the list of file names in a directory that have any of a list of extensions.
/// @param The directory path to open.
/// @return A vector of strings containing file names with that file extension.
/// @note The file extensions are compared case insensitive.
Strings GetFileNamesWithTheseExtInDir(const std::string& dirPath, Strings extensions);

/// @brief GetFileFullPathsWithExtInDir_Recursive Return the list of file name full paths with a particular extension in a directory.
/// Same as GetFileNamesWithExtInDir but it continues through the entire sub-directory hierarchy and returns the full path.
/// @param The directory path to open.
/// @return A vector of strings containing file name full paths.
/// 
Strings GetFileFullPathsWithExtInDir_Recursive(const std::string& dirPath, std::string ext);

/// @brief GetFileFullPathsWithTheseExtInDir_Recursive Return the list of file name full paths that have any of a list of extensions.
/// Same as GetFileNamesWithExtInDir but it continues through the entire sub-directory hierarchy and returns the full path.
/// @param The directory path to open.
/// @return A vector of strings containing file name full paths.
/// 
Strings GetFileFullPathsWithTheseExtInDir_Recursive(const std::string& dirPath, Strings extensions);

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

                //*******************************
                // Space Available
                //*******************************

/// @brief SpaceAvailable
/// @param A path on the drive you want the free space available
/// @return Disk space available on the drive the passed path is on
std::uintmax_t SpaceAvailable(const std::string& fileOrDirPath);

} // end namespace Tau
