#include "DirStack.h"

using namespace std;
using namespace Tau;

stack<string> savedPaths;

DirStack::DirStack(string path) : DirStack() {
    push(path);
}

DirStack::~DirStack() {
    while (!savedPaths.empty())
        pop();
}

void DirStack::push(string path) {
    savedPaths.push(GetCurrentDirPath());
    SetCurrentDirPath(path);
}

void DirStack::pop() {
    if (!savedPaths.empty()) {
        SetCurrentDirPath(savedPaths.top());
        savedPaths.pop();
    }
}
