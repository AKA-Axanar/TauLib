#pragma once
#include <string>
#include "TauLib.h"

namespace Tau { // too avoid conflict with other libraries
    std::string getExeFilePath(); // get the full path of the executing .exe or .o file
    std::string getDLLFilePath(); // get the full path of the executing .dll or .so file.  returns getExeFilePath() if not in a DLL.
    std::string getExeDirPath();  // get the full path of the directory containing the executing .exe or .o
    std::string getDLLDirPath();  // get the full path of the directory containing the executing .dll or .so.  returns getExeDirPath() if not in a DLL.
}
