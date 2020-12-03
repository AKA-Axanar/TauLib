#include "pch.h"
#include "DirFile.h"
#include <filesystem>

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

}

