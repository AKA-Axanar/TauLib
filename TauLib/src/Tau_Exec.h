#pragma once

///
/// @file
/// @brief Header file for Execute routines.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include "Str.h"

namespace Tau {


                //*******************************
                //          Execute
                //*******************************

///
/// @brief ExecuteCmd - default version of Execute.  Executes the command in the command's directory.
/// 
int ExecuteCmd(std::string command, bool waitToFinish = true, Tau::Strings arguments = {});

///
/// @brief ExecuteInCmdDir - this will save the current dir, change to the command's path, execute the command and restore the working dir.
/// 
int ExecuteInCmdDir(std::string command, bool waitToFinish = true, Tau::Strings arguments = {});

///
/// @brief ExecuteInPassedDir - this will save the current dir, change to the passed workingdir, execute the command and restore the working dir.
/// 
int ExecuteInPassedDir(std::string workingDir, std::string command, bool waitToFinish = true, Tau::Strings arguments = {});

///
/// @brief ExecuteInCurrentDir - Execute a program in another process.  
/// The other Execute routines all call this one.
/// 
// Returns the exit code of the process, or -1 if the process could not be started.
// note: we purposely pass by value so the routine can modify the args if needed
// do not enclose the command or arguments in double quotes.  the routine will take care of that if needed.
int ExecuteInCurrentDir(std::string command, bool waitToFinish = true, Tau::Strings arguments = {});

///
/// @brief DisplayURLInDefaultBrowser
/// Opens the provided URL in the default web browser.
///
bool DisplayURLInDefaultBrowser(const std::string& url);
}
