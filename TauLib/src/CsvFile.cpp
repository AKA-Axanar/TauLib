#include "CsvFile.h"
#include "DirFile.h"
#include <assert.h>
#include <algorithm>

using namespace std;
using namespace Tau;

//
// Load the csv file into 2D data structure
//
bool CsvFile::Load(const string& filepath) {
    if (!FileExists(filepath))
        return false;

    Strings fileLines = ReadTextFileAsAStringArray(filepath, /*removeCRLF*/ true);
    for (const string& line : fileLines) {
        if (isBlank(line) || isComment(line))
            continue;
        Strings pieces = SplitStringAtCommas(line, true /*trim*/);
        if (pieces.size() > numCols)
            numCols = pieces.size();
        data.emplace_back(pieces);
    }
    numRows = data.size();

    // expand the column data so all rows have the same number of columns
    for (auto& row : data) {
        while (row.size() < numCols)
            row.emplace_back("");
    }

    return true;
}

//
// Clear/Reset the class data
//
void CsvFile::Clear() {
    data.clear();
    numCols = 0;
    numRows = 0;
    opened = false;
}

//
// GetRow - return the csv values on one row
//
Strings& CsvFile::GetRow(size_t rowIndex) {
    assert(rowIndex < numRows);
    static Strings dummy;

    if (rowIndex < numRows)
        return data[rowIndex];
    else
        return dummy;
}

//
// GetRowCol - return a single row/col value
//
string& CsvFile::GetRowCol(size_t rowIndex, size_t colIndex) {
    assert(rowIndex < numRows);
    assert(colIndex < numCols);
    static string dummy;
    if (rowIndex >= numRows || colIndex >= numCols)
        return dummy;

    return data[rowIndex][colIndex];
}

// finds the row a particular column string is on.  the compare is case insensitive
// returns -1 if not found
int CsvFile::FindRowWithColumnValue(const std::string& str, size_t column) {
    for (int i = 0; i < data.size(); ++i) {
        if (data[i][column] == str)
            return i;
    }

    return -1;
}
