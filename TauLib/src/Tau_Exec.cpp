#include "Tau_Exec.h"
#include "DirFile.h"
#include "Str.h"
#include <algorithm>
#include "windows.h"
#include <iostream>
#include "DirStack.h"

///
/// @file
/// @brief Header file for Win class.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

using namespace std;
using namespace Tau;

namespace Tau {

                //*******************************
                //          Execute
                //*******************************

// default Execute - execute the command in the command's directory
int ExecuteCmd(std::string command, std::vector<std::string> arguments)
    { return ExecuteInCmdDir(command, arguments); }

// this will save the current dir, change to the command's path, execute the command and restore the working dir.
int ExecuteInCmdDir(std::string command, std::vector<std::string> arguments) {
    return ExecuteInPassedDir(GetParentPath(command), command, arguments);
}

// this will save the current dir, change to the passed workingdir, execute the command and restore the working dir.
int ExecuteInPassedDir(string workingDir, string command, vector<string> arguments) {
    DirStack dirStack(workingDir);              // save and restore the current dir
    int ret = ExecuteInCurrentDir(command, arguments);

    return ret;
}

// Execute a program in new process
// Returns the exit code of the process, or -1 if the process could not be started.
int ExecuteInCurrentDir(string command, vector<string> arguments) {

#if defined(_WIN32)
    string moduleName;

    if (icompareBool(GetFileExtensionWithoutDot(command), "bat")) {
        //
        // if batch file, change the command to "c:\\Windows\\System32\\cmd.exe /c command.bat args"
        //
        arguments.insert(begin(arguments), command);
        arguments.insert(begin(arguments), "/c");
        char cmdbuf[200];
        GetEnvironmentVariable("ComSpec", cmdbuf, sizeof(cmdbuf));
        command = cmdbuf;
        //moduleName = cmdbuf;  // pass NULL instead
    }
    else {  
        //
        // not a batch file
        //
    }

    // add double quotes around any strings that have a space
    DoubleQuoteStringIfSpace(&moduleName);
    DoubleQuoteStringIfSpace(&command);
    for_each(begin(arguments), end(arguments), 
        [&] (string& s) { DoubleQuoteStringIfSpace(&s); } );

    // concat the command and the arguments
    string cmdline = command;
    for (const string& arg : arguments) {
        cmdline.append(" ");
        cmdline.append(arg);
    };

#if 1
    cout << "moduleName: " << moduleName << endl;
    cout << "cmdline: " << cmdline << endl;
#endif

	STARTUPINFO startInfo;
	ZeroMemory(&startInfo, sizeof(startInfo));
	startInfo.cb = sizeof(startInfo);
	startInfo.dwFlags = STARTF_USESTDHANDLES;

	PROCESS_INFORMATION procInfo;
    procInfo.hProcess = INVALID_HANDLE_VALUE;
    procInfo.hThread  = INVALID_HANDLE_VALUE;
    procInfo.dwProcessId = 0;
    procInfo.dwThreadId = 0;

    DWORD procFlags = CREATE_DEFAULT_ERROR_MODE | 
                      CREATE_NO_WINDOW |
                      CREATE_NEW_PROCESS_GROUP;

    int ret = CreateProcess(
        (moduleName.empty() ? NULL : moduleName.c_str()),                   // module name
        (cmdline.empty() ? NULL : const_cast<char*>(cmdline.c_str())), 	    // Command line
        NULL, 											                    // Process handle not inheritable
        NULL, 											                    // Thread handle not inheritable
        false, 											                    // handle inheritance
        procFlags, 										                    // creation flags
        NULL, 											                    // Use parent's environment block
        NULL, 											                    // starting directory 
        &startInfo, 									                    // Pointer to STARTUPINFO structure
        &procInfo 										                    // Pointer to PROCESS_INFORMATION structure
    );

    // if error
    if (ret == 0)
	{
		int lasterror = GetLastError();

		LPTSTR strErrorMessage = NULL;
		
		// the next line was taken from GitHub
		FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_ALLOCATE_BUFFER,
			NULL,
			lasterror,
			0,
			(LPTSTR)(&strErrorMessage),
			0,
			NULL);

		cerr << "CreateProcess failed with error " << dec << lasterror << ": " << strErrorMessage << endl;
		return -1;
	}

	// Wait until child process exits.
	WaitForSingleObject(procInfo.hProcess, INFINITE);

	DWORD exitCode;
	GetExitCodeProcess(procInfo.hProcess, &exitCode);

	// Close process and thread handles.
	CloseHandle(procInfo.hProcess);
	CloseHandle(procInfo.hThread);

	return exitCode;
}
#else
    vector<const char *> argvNew;

    string link = command;
    argvNew.push_back(link.c_str());
    for (const string& arg : args)
        argvNew.push_back(arg.c_str());
    argvNew.push_back(nullptr);

#if 1
    cout << "CMD line to execute: ";
    for (const char *s:argvNew) {
        if (s != nullptr) {
            cout << s << " ";
        }
    }
    cout << endl;
#endif

    int pid = fork();
    if (!pid) {
        execvp(link.c_str(), (char **) argvNew.data());
    }
    waitpid(pid, NULL, 0);
    Sleep_MilliSeconds(300);
#endif

}
