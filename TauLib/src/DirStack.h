#pragma once

///
/// @file
/// @brief Header file for DirStack class.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

#include "DirFile.h"
#include <stack>

///
/// @class DirStack class.  Saves and restores the current working path on a stack.
///
class DirStack {
    std::stack<std::string> savedPaths;

public:
    DirStack() {}

    DirStack(std::string path);         // save current wokring path.  change working path.
    ~DirStack();                        // pop off all saved paths restoring to the original.

    void push(std::string path);        // save current wokring path.  change working path.
    void pop();                         // restores to the last pushed working path
};
