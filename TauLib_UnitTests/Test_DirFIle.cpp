#include "pch.h"
#include "DirFile.h"
#include <filesystem>
#include "sep.h"
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

    temp = GetFileExtension("a/b/foo.dat");
    EXPECT_EQ(temp, ".dat");
    temp = GetFileExtensionWithoutDot("a/b/foo.dat");
    EXPECT_EQ(temp, "dat");

    temp = GetFilename("aaa/bbb/foo.dat");
    EXPECT_EQ(temp, "foo.dat");

    temp = GetFilenameBase("aaa/bbb/foo.dat");
    EXPECT_EQ(temp, "foo");

    temp = GetParentPath("aaa/bbb/foo.dat");
    EXPECT_EQ(temp, "aaa/bbb");
    temp = GetParentPath("aaa/bbb");
    EXPECT_EQ(temp, "aaa");

    temp = ReplaceFilename("aaa/bbb/foo.dat", "bar.dat");
    EXPECT_EQ(temp, "aaa/bbb/bar.dat");
    temp = ReplaceFileExtension("aaa/bbb/foo.dat", ".txt");
    EXPECT_EQ(temp, "aaa/bbb/foo.txt");
    temp = ReplaceFileExtension("aaa/bbb/foo.dat", "txt");
    EXPECT_EQ(temp, "aaa/bbb/foo.txt");
    temp = RemoveFilename("aaa/bbb/foo.dat");
    EXPECT_EQ(temp, "aaa/bbb/");

    //cout << "PWD: " << GetCurrentPath() << endl;
    string testDir { "DirFileTestArea" };
    CreateDirPath(testDir);
    EXPECT_EQ(DirExists(testDir), true);

    string subDir = testDir + sep + "a" + sep + "b";
    CreateDirPath(subDir);
    EXPECT_EQ(DirExists(subDir), true);

    string subDira = testDir + sep + "a";
    string subDira2 = testDir + sep + "a2";
    CopyDirOverwrite(subDira, subDira2);
    EXPECT_EQ(DirExists(subDira2), true);

    DeleteDirectory(subDira);
    EXPECT_EQ(DirExists(subDira), false);

    string filename = testDir + sep + "file.txt";
    string filename2 = testDir + sep + "file.txt";
    ofstream(filename).put('a');
    RenameFile(filename, filename2);
    EXPECT_EQ(FileExists(filename2), true);

    DeleteDirectory(testDir);
}

