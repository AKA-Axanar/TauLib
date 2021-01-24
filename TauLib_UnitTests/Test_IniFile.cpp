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
    // load an existing ini file, edit, save, and compare to expectd output
    IniFile iniTest("ini_Input.ini");
    iniTest.SetKeyValue("Logo", "Tau.png", "Theme");
    iniTest.SetKeyValue("Font", "z.ttf", "Theme");
    iniTest.SetKeyValue("new", "xxx", "");
    iniTest.DeleteKey("alpha", "Theme");
    EXPECT_EQ(iniTest.GetKeyValue("Datetimeformat", "Theme"), "%F %I:%M:%S %p");
    EXPECT_EQ(iniTest.GetKeyValue_Int("top", "Theme"), 20);
    auto temp = iniTest.GetKeyValue_Ints("point", "Theme");
    EXPECT_TRUE(temp.size() == 2);
    EXPECT_TRUE(temp[0] == 200);
    EXPECT_TRUE(temp[1] == 100);
    iniTest.SaveAs("ini_TestResult.ini");
    EXPECT_TRUE(CompareFiles("testResult.ini", "testOut.ini"));

    // create a new ini file, add keys and sections, save, and compare to expectd output
    IniFile newIni;
    newIni.SetKeyValue("line1", "value1");
    newIni.SetKeyValue("line2", "value2");
    newIni.SetKeyValue("line3", "value3", "config");
    newIni.SetKeyValue("line4", "value4", "config");
    newIni.SetKeyValue("line_5", "value_5", "config");
    newIni.SetKeyValue("line2.1", "value2.1");
    newIni.SaveAs("ini_TestResult2.ini");
    EXPECT_TRUE(CompareFiles("testResult2.ini", "testOut2.ini"));
}
