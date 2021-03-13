#include "Tau_Util.h"
#include "CommandLine.h"

namespace Tau {

void Sleep_Minutes(int delay) {
    std::this_thread::sleep_for(std::chrono::minutes(delay));
}

void Sleep_Seconds(int delay) {
    std::this_thread::sleep_for(std::chrono::seconds(delay));
}

void Sleep_MilliSeconds(int delay) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

void Sleep_MicroSeconds(int delay) {
    std::this_thread::sleep_for(std::chrono::microseconds(delay));
}

// Returns the exit code of the process, or -1 if the process could not be started.
int Execute(const std::string& command, const std::vector<std::string>& arguments) {
    CommandLine cmdline(command, arguments);
    return cmdline.executeAndWait();
}

}
