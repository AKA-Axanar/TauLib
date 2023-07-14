// from https://www.youtube.com/watch?v=oEx5vGNFrLk and modified

#include "Tau_Timer.h"
#include <iostream>

using namespace std;

using namespace std::literals::chrono_literals;

//
// To time an event, create a Tau_Timer object at the start of the event, and it will print the duration when it goes out of scope.
// To time an function put Tau_Timer timer(__FUNCTION__) at the start of the function.
// Or put Tau_Timer timer(__FUNCTION__, __FILE__, __LINE__) at the start of the function.
// Or put Timer timer("some other text"); anywhere you want.
//

int Tau_Timer::nesting_level {0};

// start the timer
Tau_Timer::Tau_Timer(const string& _text, const string& _filename, int _lineNum) 
         : text { _text }, filename{_filename}, lineNum{_lineNum} {
#ifdef _DEBUG
    start = std::chrono::steady_clock::now();
    last = start;

    string indent(nesting_level * 2, ' ');
    auto [duration_ms, delta_ms] = GetDurationAndDelta();
    if (filename != "")
        std::cout << indent << text << " START" << " file = " << filename << " line " << lineNum << std::endl;
    else
        std::cout << indent << text << " START" << std::endl;

    ++nesting_level;
#endif
  }

// output the duration of the timer object
Tau_Timer::~Tau_Timer() {
#ifdef _DEBUG
    --nesting_level;

    string indent(nesting_level * 2, ' ');
    auto [duration_ms, delta_ms] = GetDurationAndDelta();
    if (filename != "")
        std::cout << format("{}{} END duration = {:g} ms delta = {:g} ms", indent, text, duration_ms, delta_ms) << " file = " << filename << " line " << lineNum << std::endl;
    else
        std::cout << format("{}{} END duration = {:g} ms delta = {:g} ms", indent, text, duration_ms, delta_ms) << std::endl;
#endif
}

// return the current duration in milliseconds
pair<float, float> Tau_Timer::GetDurationAndDelta() {
#ifdef _DEBUG
    string indent(nesting_level * 2, ' ');
    auto now = std::chrono::steady_clock::now();
    auto duration = now - start;
    auto delta = now - last;
    last = now;
    float duration_ms = duration.count() / 1'000'000.0f;
    float delta_ms = delta.count() / 1'000'000.0f;
    return {duration_ms, delta_ms};
#else
    return {0.0f,0.0f};
#endif
}

// output the current duration in milliseconds
void Tau_Timer::printDurationNow(const string& _text, const string& _filename, int _lineNum) {
#ifdef _DEBUG
    string indent(nesting_level * 2, ' ');
    auto [duration_ms, delta_ms] = GetDurationAndDelta();
    if (filename != "")
        std::cout << format("{}{} duration = {:g} ms delta = {:g} ms", indent, _text, duration_ms, delta_ms) << " file = " << _filename << " line " << _lineNum << std::endl;
    else
        std::cout << format("{}{} duration = {:g} ms delta = {:g} ms", indent, _text, duration_ms, delta_ms) << std::endl;
#endif
}

#if 0
void Function2() {
    Tau_Timer timer(__FUNCTION__);
    std::this_thread::sleep_for(2s);
    // dtor should output approx 2 seconds
}

void Function1() {
   Tau_Timer timer(__FUNCTION__);
    Function2();
    std::this_thread::sleep_for(1s);
    // dtor should output approx 3 seconds
}


void Tau_TimerTest() {
    Tau_Timer timer(__FUNCTION__);
    Function1();
    std::this_thread::sleep_for(5s);
    timer.printDurationNow("should be 8");
    std::this_thread::sleep_for(500ms);
    timer.printDurationNow("should be 8.5");
    std::this_thread::sleep_for(500ms);
    // dtor should output approx 8 seconds
}
#endif

