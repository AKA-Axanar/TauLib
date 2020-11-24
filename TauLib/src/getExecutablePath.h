#pragma once
#include <string>
#include "TauLib.h"

namespace Tau { // too avoid conflict with other libraries
    std::string getExeFilePath();       // get the full path of the executing .exe or .o path
    std::string getDLLFilePath();       // get the full path of the executing .dll or .so path.  returns getExeFilePath() if not in a DLL.
    std::string getExeFileParentDir();  // get the full path of the executing .exe or .o parent dir
    std::string getDLLFileParentDir();  // get the full path of the executing .dll or .so parent dir.  returns getExeFileParentPath() if not in a DLL.
}
