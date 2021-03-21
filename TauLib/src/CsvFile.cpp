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
Strings CsvFile::GetRow(size_t rowIndex) {
    assert(rowIndex < numRows);
    if (rowIndex < numRows)
        return data[rowIndex];
    else
        return Strings();
}

//
// GetRowCol - return a single row/col value
//
string CsvFile::GetRowCol(size_t rowIndex, size_t colIndex) {
    assert(rowIndex < numRows);
    if (rowIndex < numRows)
        return "";
    else {
        const Strings& row = data.at(rowIndex);
        if (colIndex < row.size())
            return row[colIndex];
        else
            return "";
    }
}

// finds the row a particular column string is on.  the compare is case insensitive
std::vector<CsvLine>::iterator CsvFile::FindRowWithColumnValue(const std::string& str, size_t column) {
    auto it = find_if(begin(data), end(data), [&] (const Strings& line) { 
        if (column >= line.size())
            return false;
        return icompareBool(line[column], str);
    });

    return it;
}
