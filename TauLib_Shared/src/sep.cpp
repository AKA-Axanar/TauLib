#include "sep.h"
using namespace std;

namespace Tau {

//*******************************
// append separator helper function
//*******************************
// example:  somepath is a string of a path but you do not know for sure if there is or is not a "/" at the end or not
// somepath + sep + "font" + sep + "default.ttf" will append the separator to somepath only if it's not there
string operator + (const string& leftside, Sep) {
    string ret = leftside;
    ret += sep;

    return ret;
}

//*******************************
// append separator helper function
//*******************************
// to use "operator +" below, "path + sep" will append the separator only if it's not already on the end of path
void operator += (std::string& leftside, Sep) {
    if (leftside.size() > 0)
    {
        char lastChar = leftside.back();
        if (lastChar != separator)
            leftside += separator; // add slash at end
    }
}
}
