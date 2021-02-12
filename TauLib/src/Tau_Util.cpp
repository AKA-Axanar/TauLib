#include "Tau_Util.h"

namespace Tau {

void Sleep_Seconds(int delay) {
    std::this_thread::sleep_for(std::chrono::seconds(delay));
}

void Sleep_MilliSeconds(int delay) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

void Sleep_MicroSeconds(int delay) {
    std::this_thread::sleep_for(std::chrono::microseconds(delay));
}

void Sleep_MinutesSeconds(int delay) {
    std::this_thread::sleep_for(std::chrono::minutes(delay));
}

}
