#pragma once
///
/// @file
/// @brief Header file for time routines.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <ctime>

namespace Tau {

// get current time
time_t CurrentTimeAsTime_t();
std::chrono::system_clock::time_point CurrentTimeAsTime_point();

// time to string
std::string Time_t_ToString(time_t t=0, const std::string& format="");
std::string CurrentTime_ToString(const std::string& format="");

// delay routines
void Sleep_Minutes(int delay);
void Sleep_Seconds(int delay);
void Sleep_MilliSeconds(int delay);
void Sleep_MicroSeconds(int delay);
}