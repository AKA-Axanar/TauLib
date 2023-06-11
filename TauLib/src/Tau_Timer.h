#pragma once

// from https://www.youtube.com/watch?v=oEx5vGNFrLk and modified

#include <chrono>
#include <string>
#include <iostream>

//
// To time an event, create a Tau_Timer object at the start of the event, and it will print the duration when it goes out of scope.
// To time an function put Tau_Timer timer(__FUNCTION__) at the start of the function.
// Or put Tau_Timer timer(__FUNCTION__, __FILE__, __LINE__) at the start of the function.
// Or put Timer timer("some other text"); anywhere you want.
//
struct Tau_Timer {
    std::chrono::time_point<std::chrono::steady_clock> start, last;
    std::string text, filename;
    int lineNum;
    static int nesting_level;

    Tau_Timer(const std::string& _text="", const std::string& _filename = "", int _lineNum = 0);
    ~Tau_Timer();

    std::pair<float, float> GetDurationAndDelta();
    void printDurationNow(const std::string& _text="", const std::string& _filename = "", int _lineNum = 0);
};

void Tau_TimerTest();

