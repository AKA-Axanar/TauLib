#pragma once

// if you are linking to the DLL lib then define USINGTAULIB_DLL
// if you are linking to the static lib then do not define it.  TAULIBDLL_API will then be blank.

#if defined(USINGTAULIB_DLL) || defined(TAULIBDLL_EXPORTS)
    #ifdef TAULIBDLL_EXPORTS
        #define TAULIBDLL_API __declspec(dllexport)
    #else
        #define TAULIBDLL_API __declspec(dllimport)
    #endif
#else
    #define TAULIBDLL_API
#endif


