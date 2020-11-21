#pragma once
#include <string>
#include "TauLib.h"

namespace Tau {
    std::string TAULIBDLL_API getExePath();     // get the executing .exe or .o path
    std::string TAULIBDLL_API getDLLPath();     // get the executing .dll or .so path.  returns getExePath() if not in a DLL.
}
