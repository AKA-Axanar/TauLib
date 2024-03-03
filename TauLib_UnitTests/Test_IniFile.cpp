#include "pch.h"
#include "IniFile.h"
#include "IniFileWithDefault.h"
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
    iniTest.SetKeyValue_Int("value", 100, "Theme");
    EXPECT_EQ(iniTest.GetKeyValue_Int("value", "Theme"), 100);
    iniTest.SetKeyValue_Ints("rect", {10,20,100,200}, "Theme");
    temp = iniTest.GetKeyValue_Ints("rect", "Theme");
    EXPECT_EQ(temp[0], 10);
    EXPECT_EQ(temp[1], 20);
    EXPECT_EQ(temp[2], 100);
    EXPECT_EQ(temp[3], 200);

    iniTest.SaveAs("ini_TestResult.ini");
//    EXPECT_TRUE(CompareFiles("ini_TestResult.ini", "ini_Output.ini"));

    // create a new ini file, add keys and sections, save, and compare to expectd output
    IniFile newIni;
    newIni.GetKeyValue_Int("doesntExist");      // shouldn't crash
    newIni.GetKeyValue_Ints("doesntExist");     // shouldn't crash
    newIni.SetKeyValue("line1", "value1");
    newIni.SetKeyValue("line2", "value2");
    newIni.SetKeyValue("line3", "value3", "config");
    newIni.SetKeyValue("line4", "value4", "config");
    newIni.SetKeyValue("line_5", "value_5", "config");
    newIni.SetKeyValue("line2.1", "value2.1");
    newIni.SaveAs("ini_TestResult2.ini");
    EXPECT_TRUE(CompareFiles("ini_testResult2.ini", "ini_Output2.ini"));

    // test an ini file with a default ini file that is searched if the key is not found in the first ini file.
    IniFileWithDefault masterIni("ini_master.ini", "ini_default.ini");
    string alpha = masterIni.GetKeyValue("alpha");  
    string beta = masterIni.GetKeyValue("beta");    
    string gamma = masterIni.GetKeyValue("gamma");  
    EXPECT_EQ(alpha, "alpha_master");               // this key is in both master and the default.ini.  it should return the master.
    EXPECT_EQ(beta, "beta_default");                // this key is not in master but is in the default.  it should return the default.
    EXPECT_EQ(gamma , "");                          // this key is in neither ini file.  it should return "".
}
