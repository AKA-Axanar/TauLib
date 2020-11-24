#include "getExecutablePath.h"
#include <string>
#include "whereami.h"
#include <memory>
#include <string>
#include <filesystem>

using namespace std;

namespace Tau { // too avoid conflict with other libraries

//
// get the executing .exe or .o path
//
string getExeFilePath() {
    int length = wai_getExecutablePath(NULL, 0, NULL);
    unique_ptr<char[]> buf = make_unique<char[]>(length + 1);
    wai_getExecutablePath(buf.get(), length, NULL);

    return buf.get();
}

//
// get the executing .dll or .so path.  returns getExePath() if not in a DLL.
//
string getDLLFilePath() {
    int length = wai_getModulePath(NULL, 0, NULL);
    unique_ptr<char[]> buf = make_unique<char[]>(length + 1);
    wai_getModulePath(buf.get(), length, NULL);

    return buf.get();
}

//
// get the executing .exe or .o parent dir
//
string getExeFileParentDir() {
    filesystem::path p(getExeFilePath());
    auto parent = p.parent_path();
    return parent.string();
}

//
// get the executing .dll or .so parent dir.  returns getExeFileParentPath() if not in a DLL.
//
string getDLLFileParentDir() {
    filesystem::path p(getDLLFilePath());
    auto parent = p.parent_path();
    return parent.string();
}

}