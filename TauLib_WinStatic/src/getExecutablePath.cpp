#include "getExecutablePath.h"
#include <string>
#include "whereami.h"
#include <memory>

using namespace std;

namespace Tau {

// get the executing .exe or .o path
string getExePath() {
    int length = wai_getExecutablePath(NULL, 0, NULL);
    unique_ptr<char[]> buf = make_unique<char[]>(length + 1);
    wai_getExecutablePath(buf.get(), length, NULL);

    return buf.get();
}

// get the executing .dll or .so path
string TAULIBDLL_API getDLLPath() {
    int length = wai_getModulePath(NULL, 0, NULL);
    unique_ptr<char[]> buf = make_unique<char[]>(length + 1);
    wai_getModulePath(buf.get(), length, NULL);

    return buf.get();
}

}