#pragma once
#include <string>
#include "TauLib.h"

///
/// @file
/// @brief Header file for getting the path of the executing exe or dll.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///

///
/// @brief namespace Tau - avoid conflict with other libraries
///
namespace Tau { // to avoid conflict with other libraries
    std::string getExeFilePath(); ///< @brief get the full path of the executing .exe or .o file
    std::string getDLLFilePath(); ///< @brief get the full path of the executing .dll or .so file.  returns getExeFilePath() if not in a DLL.
    std::string getExeDirPath();  ///< @brief get the full path of the directory containing the executing .exe or .o
    std::string getDLLDirPath();  ///< @brief get the full path of the directory containing the executing .dll or .so.  returns getExeDirPath() if not in a DLL.
}
