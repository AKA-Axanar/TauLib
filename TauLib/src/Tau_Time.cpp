#include "Tau_Time.h"
///
/// @file
/// @brief CPP file for time routines.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

using namespace std;

namespace Tau {

                //*******************************
                //           Current Time
                //*******************************
//
// CurrentTimeAsTime_t
//
time_t CurrentTimeAsTime_t()
{
    auto current = chrono::system_clock::now();
    time_t now = chrono::system_clock::to_time_t(current);
    return now;
}

//
// CurrentTimeAsTime_point
//
chrono::system_clock::time_point CurrentTimeAsTime_point()
{
    auto current = chrono::system_clock::now();
    return current;
}

//
// Time_t_ToString
//
string Time_t_ToString(time_t t, const string& format)
{
    if (t == 0)
        t = CurrentTimeAsTime_t();

    char buf[200];
    if (format != "") {
        struct tm tm_buf;
        auto err_no = localtime_s(&tm_buf, &t);
        if (err_no == 0) {
            if (strftime(buf, sizeof(buf), format.c_str(), &tm_buf))
                return buf;
            else {
                ctime_s(buf, sizeof(buf), &t);   // error with the format, use default
                return buf;
            }
        } else {
            ctime_s(buf, sizeof(buf), &t);   // error with the format, use default
            return buf;
        }
    } else {
        ctime_s(buf, sizeof(buf), &t);   // error with the format, use default
        return buf;
    }
}

//
// CurrentTime_TosString
//
string CurrentTime_ToString(const string& format)
{
    return Time_t_ToString(CurrentTimeAsTime_t(), format);
}

                //*******************************
                //           Sleep
                //*******************************
//
// Sleep_Minutes
//
void Sleep_Minutes(int delay) {
    this_thread::sleep_for(chrono::minutes(delay));
}

//
// Sleep_Seconds
//
void Sleep_Seconds(int delay) {
    this_thread::sleep_for(chrono::seconds(delay));
}

//
// Sleep_MilliSeconds
//
void Sleep_MilliSeconds(int delay) {
    this_thread::sleep_for(chrono::milliseconds(delay));
}

//
// Sleep_MicroSeconds
//
void Sleep_MicroSeconds(int delay) {
    this_thread::sleep_for(chrono::microseconds(delay));
}

}
