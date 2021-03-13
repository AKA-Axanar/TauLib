// I found this class source code at https://gist.github.com/multiplemonomials/1d1806062a3809ffe26f7a232757ecb6
// and split the cpp file into a header and cpp file.

#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <cstdio>
#include <iostream>

#if defined(_WIN32)
#	include <fcntl.h>
#	include <windows.h>
#	define STDERR_FILENO 2
#	define STDIN_FILENO 0
#	define STDOUT_FILENO 1
#else
#	include <unistd.h>
#	include <sys/wait.h>
#endif

// Class to handle building command lines for both execvp and CreateProcess
// the main issue is that CreateProcess requires paths with spaces to be quoted, while execvp doesn't understand that syntax.
class CommandLine
{
	std::string _program;
	std::vector<std::string> _arguments;

	std::string quoteIfNecessary(std::string toQuote);

	public:

	//construct with full path to or name of program to execute
	CommandLine(const std::string& program);
	CommandLine(const std::string& program, const std::vector<std::string>& arguments);

	// adds an argument.  This is NOT a simple string concatenation; the argument should be one element of the target program's argv array.
	// Spaces will be quoted automatically if necessary.
	CommandLine& arg(const std::string& arg);

	// Get a command line with the program and its arguments, like you'd type into a shell or pass to CreateProcess()
	// Arguments with spaces will be double quoted.
	std::string getCommandlineString();

	// Execute the command and arguments, setting its standard streams to the three provided if they are not 0.
	// Blocks until it finishes.
	// If the command is not an absolute path, it will be searched for in the system PATH.
	// Returns the exit code of the process, or -1 if the process could not be started.

	int executeAndWait(int sin, int sout, int serr);
	int executeAndWait() { return executeAndWait(0,0,0); }
};