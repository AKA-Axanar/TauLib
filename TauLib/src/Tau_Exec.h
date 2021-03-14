#pragma once

///
/// @file
/// @brief Header file for Win class.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

#include <thread>
#include <chrono>
#include <vector>
#include <string>

namespace Tau {


                //*******************************
                //          Execute
                //*******************************

///
/// @brief ExecuteCmd - default version of Execute.  Executes the command in the command's directory.
/// 
int ExecuteCmd(std::string command, std::vector<std::string> arguments = {});

///
/// @brief ExecuteInCmdDir - this will save the current dir, change to the command's path, execute the command and restore the working dir.
/// 
int ExecuteInCmdDir(std::string command, std::vector<std::string> arguments = {});

///
/// @brief ExecuteInPassedDir - this will save the current dir, change to the passed workingdir, execute the command and restore the working dir.
/// 
int ExecuteInPassedDir(std::string workingDir, std::string command, std::vector<std::string> arguments = {});

///
/// @brief ExecuteInCurrentDir - Execute a program in another process.  
/// The other Execute routines all call this one.
/// 
// Returns the exit code of the process, or -1 if the process could not be started.
// note: we purposely pass by value so the routine can modify the args if needed
// do not enclose the command or arguments in double quotes.  the routine will take care of that if needed.
int ExecuteInCurrentDir(std::string command, std::vector<std::string> arguments = {});

}
