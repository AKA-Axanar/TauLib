#include "getExecutablePath.h"
#include <string>
#include <memory>
#include <filesystem>
#include "whereami.h"

using namespace std;

namespace Tau { // to avoid conflict with other libraries

//
// get the executing .exe or .o path file
//
string getExeFilePath() {
    int length = wai_getExecutablePath(NULL, 0, NULL);
    unique_ptr<char[]> buf = make_unique<char[]>(length + 1);
    wai_getExecutablePath(buf.get(), length, NULL);

    return buf.get();
}

//
// get the executing .dll or .so path file.  returns getExePath() if not in a DLL.
//
string getDLLFilePath() {
    int length = wai_getModulePath(NULL, 0, NULL);
    unique_ptr<char[]> buf = make_unique<char[]>(length + 1);
    wai_getModulePath(buf.get(), length, NULL);

    return buf.get();
}

//
// get the full path of the directory containing the executing .exe or .o
//
string getExeDirPath() {
    filesystem::path p(getExeFilePath());
    auto parent = p.parent_path();
    return parent.string();
}

//
// get the full path of the directory containing the executing .dll or .so.  returns getExeDirPath() if not in a DLL.
//
string getDLLDirPath() {
    filesystem::path p(getDLLFilePath());
    auto parent = p.parent_path();
    return parent.string();
}

} // end namespace Tau