#pragma once

// if you are linking to the DLL lib then define USINGTAULIB_DLL
// if you are linking to the static lib then do not define it.  TAULIBDLL_API will then be blank.

// if building the DLL or linking to the DLL lib then define TAULIBDLL_API to 
// either export or import the function symbols.
#if defined(USINGTAULIB_DLL) || defined(TAULIBDLL_EXPORTS)
    #ifdef TAULIBDLL_EXPORTS
		// we're building the DLL and exporting the symbols in the LIB
        #define TAULIBDLL_API __declspec(dllexport)
    #else
		// we're consuming the DLL and importing the stmbols from the LIB
        #define TAULIBDLL_API __declspec(dllimport)
    #endif
#else
	// define as nothing
    #define TAULIBDLL_API
#endif


