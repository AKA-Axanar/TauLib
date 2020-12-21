#include "pch.h"
#include "IniFile.h"
#include "DirFile.h"
#include "GetExecutablePath.h"

using namespace std;
using namespace Tau;

//
// test DirFile routines.
//
TEST(TestIniFile, TestIniFile) {
    IniFile iniTest("ini_Input.ini");
    iniTest.SetKeyValue("Logo", "Tau.png", "Theme");
    iniTest.SetKeyValue("Font", "z.ttf", "Theme");
    iniTest.SetKeyValue("new", "xxx", "");
    iniTest.DeleteKey("alpha", "Theme");
    iniTest.SaveAs("ini_TestResult.ini");
    EXPECT_TRUE(CompareFiles("testResult.ini", "testOut.ini"));
}
