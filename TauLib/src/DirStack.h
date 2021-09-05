#pragma once
///
/// @file
/// @brief Header file for DirStack class.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

#include "DirFile.h"
#include <stack>

///
/// @brief Saves and restores the current working path on a stack.
///
class DirStack {
    std::stack<std::string> savedPaths; ///< stack of saved dir paths

public:
    /// @brief DirStack default ctor
    DirStack() {}

    /// @brief ctor - save current working path.  change working path.
    DirStack(const std::string& path);

    /// @brief dtor - pop off all saved paths restoring to the original.
    ~DirStack();

    /// @brief push - save current working path.  change working path.
    void push(const std::string& path);
    /// @brief pop - restores to the last pushed working path
    void pop();
};
