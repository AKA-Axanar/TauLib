#pragma once

#include <thread>
#include <chrono>
#include <vector>
#include <string>

namespace Tau {

void Sleep_Minutes(int delay);
void Sleep_Seconds(int delay);
void Sleep_MilliSeconds(int delay);
void Sleep_MicroSeconds(int delay);

// Returns the exit code of the process, or -1 if the process could not be started.
int Execute(const std::string& command, const std::vector<std::string>& arguments = {});

}
