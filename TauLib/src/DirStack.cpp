#include "DirStack.h"

using namespace std;
using namespace Tau;

stack<string> savedPaths;

// ctor - save current working path.  change working path.
DirStack::DirStack(const string& path) : DirStack() {
    push(path);
}

// dtor - pop off all saved paths restoring to the original.
DirStack::~DirStack() {
    while (!savedPaths.empty())
        pop();
}

// push - save current working path.  change working path.
void DirStack::push(const string& path) {
    savedPaths.push(GetCurrentDirPath());
    SetCurrentDirPath(path);
}

// pop - restores to the last pushed working path
void DirStack::pop() {
    if (!savedPaths.empty()) {
        SetCurrentDirPath(savedPaths.top());
        savedPaths.pop();
    }
}
