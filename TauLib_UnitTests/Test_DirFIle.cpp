#include "pch.h"
#include "DirFile.h"
#include <filesystem>
#include "Sep.h"
#include <fstream>

using namespace std;
using namespace Tau;
namespace fs = std::filesystem;

//
// test DirFile routines.
//
TEST(TestDirFile, TestDirFile) {
    string temp;
    string ret;

    temp = GetFileExtensionWithDot("a/b/foo.dat");
    EXPECT_EQ(temp, ".dat");
    temp = GetFileExtensionWithoutDot("a/b/foo.dat");
    EXPECT_EQ(temp, "dat");

    temp = GetFilename("aaa/bbb/foo.dat");
    EXPECT_EQ(temp, "foo.dat");

    temp = GetFilename("aaa/bbb/ccc");
    EXPECT_EQ(temp, "ccc");

    temp = GetFilenameBase("aaa/bbb/foo.dat");
    EXPECT_EQ(temp, "foo");

    temp = GetFilenameBase("aaa/bbb/ccc");
    EXPECT_EQ(temp, "ccc");

    temp = GetParentPath("aaa/bbb/foo.dat");
    EXPECT_EQ(temp, "aaa/bbb");
    temp = GetParentPath("aaa/bbb");
    EXPECT_EQ(temp, "aaa");

    temp = ReplaceFilename("aaa/bbb/foo.dat", "bar.txt");
    EXPECT_EQ(temp, "aaa/bbb/bar.txt");
    temp = ReplaceFileExtension("aaa/bbb/foo.dat", ".txt");
    EXPECT_EQ(temp, "aaa/bbb/foo.txt");
    temp = ReplaceFileExtension("aaa/bbb/foo.dat", "txt");
    EXPECT_EQ(temp, "aaa/bbb/foo.txt");
    temp = RemoveFilenameFromPath("aaa/bbb/foo.dat");
    EXPECT_EQ(temp, "aaa/bbb/");

    //cout << "PWD: " << GetCurrentPath() << endl;
    string testDir { "DirFileTestArea" };
    CreateDir(testDir);
    EXPECT_EQ(DirExists(testDir), true);

    string subDir = testDir + sep + "a" + sep + "b";
    CreateDir(subDir);
    EXPECT_EQ(DirExists(subDir), true);

    string subDira = testDir + sep + "a";
    string subDira2 = testDir + sep + "a2";
    CopyDir(subDira, subDira2);
    EXPECT_EQ(DirExists(subDira2), true);

    DeleteDir(subDira);
    EXPECT_EQ(DirExists(subDira), false);

    string filename = testDir + sep + "file.txt";
    string filename2 = testDir + sep + "file2.txt";
    ofstream(filename).put('a');
    RenameFile(filename, filename2);
    EXPECT_EQ(FileExists(filename2), true);

    string filenameDat = testDir + sep + "file.dat";
    CopyFile(filename2, filenameDat);
    auto filenames = GetFileNamesWithExtInDir(testDir, ".dat");
    EXPECT_EQ(filenames.size(), 1);
    EXPECT_EQ(filenames[0], "file.dat");

    DeleteDir(testDir);

    // test reading a file into a Strings array
    string filePath = GetATempFilename();
    ofstream ofile(filePath, std::ofstream::out);
    ofile << "one" << endl;     // purposely adding a cr,lf or lf at the end to test removal in ReadTextFileAsAStringArray()
    ofile << "two" << endl;
    ofile << "three" << endl;
    ofile.close();
    Strings contents = ReadTextFileAsAStringArray(filePath, true);
    EXPECT_TRUE(contents.size() == 3);
    EXPECT_EQ(contents[0], "one");
    EXPECT_EQ(contents[1], "two");
    EXPECT_EQ(contents[2], "three");
    DeleteFile(filePath);
}

