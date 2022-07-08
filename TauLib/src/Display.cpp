#include "Display.h"


using namespace std;

namespace Tau {

    // GetDisplayInfos -  return info about the displays attached to the system
    vector<DisplayInfo> Display::GetDisplayInfos() {
        unsigned int count = GetNumberOfDisplays();
        vector<DisplayInfo> ret;

        for (unsigned int i = 0; i < count; ++i) {
            DisplayInfo info;
            info.displayIndex = i;
            info.posit = GetDisplayPositFlag(i);
            info.size = GetDisplaySize(i);
            info.bounds = { info.posit, info.size };

            ret.emplace_back(info);
        }
        return ret;
    }
}
