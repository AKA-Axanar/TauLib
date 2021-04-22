#include "CsvFile.h"
#include "DirFile.h"
#include <assert.h>
#include <algorithm>
#include <fstream>
#include "sep.h"

using namespace std;
using namespace Tau;

//
// Load the csv file into 2D data structure
//
bool CsvFile::Load(const string& filepath) {
    if (!FileExists(filepath))
        return false;

    csvFilePath = filepath;

    Strings fileLines = ReadTextFileAsAStringArray(filepath, /*removeCRLF*/ true);
    for (const string& line : fileLines) {
        AddString(line);
    }

    return true;
}

//
// ReLoad
//
bool CsvFile::ReLoad()
{
    if (csvFilePath != "") {
        Clear();
        return Load(csvFilePath);
    }
    return false;
}

//
// Clear/Reset the class data
//
void CsvFile::Clear() {
    rows.clear();
    opened = false;
}

//
// SaveAs
//
bool CsvFile::SaveAs(const std::string& filepath)
{
    ofstream ofile(filepath.c_str(), ofstream::out | ofstream::trunc);
    if (!ofile.is_open())
        return false;

    for (const Strings& row : rows) {
        bool firstItem = true;
        for (const string& item : row) {
            if (!firstItem)
                ofile << ", ";
            ofile << item;
            firstItem = false;
        }
        ofile << lineEnding;
    }
    ofile.close();

    return true;
}

//
// Save
//
bool CsvFile::Save()
{
    if (csvFilePath == "")
        return false;

    return SaveAs(csvFilePath);
}

//
// AddString - add a string of comma separated values
//
void CsvFile::AddString(const std::string& line)
{
    if (isBlank(line) || isComment(line))
        return;

    Strings row = SplitStringAtCommas(line, true /*trim*/);
    AddRow(row);
}

//
// AddRow - add a row of strings
//
bool CsvFile::AddRow(const Strings& row)
{
    if (row.size() > 0) {
        rows.emplace_back(row);
        return true;
    } else
        return false;
}

//
// RemoveRow
//
void CsvFile::RemoveRow(unsigned int rowIndex)
{
    assert(rowIndex < rows.size());
    if (rowIndex < rows.size())
        rows.erase(rows.begin() + rowIndex);
}

void CsvFile::Sort(unsigned int column)
{
    sort(rows.begin(), rows.end(), [&] (const Strings& row1, const Strings& row2) { return row1[column] < row2[column]; } );
}

//
// 
// finds the first row where the passed rowItems match the first items in the row.
// it does not fail if there are more items in the row than being passed.
// returns the index of the first row that matches.  returns -1 if a row was not found with those items.
//
int CsvFile::FindRow(const Tau::Strings& searchItems)
{
    assert(searchItems.size() > 0);
    if (searchItems.size() == 0)
        return -1;      // nothing was passed

    unsigned int rowIndex = 0;
    for (const Strings& row : rows) {
        if (searchItems.size() > row.size())
            continue;   // skip

        bool match = true;
        for (unsigned int i = 0; i < searchItems.size(); ++i) {
            if (searchItems[i] != row[i]) {
                match = false;
                break;  // this row does not match
            }
        }
        if (match)
            return rowIndex;        // match found

        ++rowIndex;
    }
    return 0;
}

//
// RowExists
// returns true if the passed items exist at the front of a row
//
bool CsvFile::RowExists(const Tau::Strings& searchItems)
{
    return FindRow(searchItems) != -1;
}

//
// ExpandToSameNumberOfColumns
//
// find the max number of columns used and expand all rows to that size.
// returns the number of columns
size_t CsvFile::ExpandToSameNumberOfColumns()
{
    // find the max number of columns used
    size_t numCols = 0;
    for (const auto& row : rows) {
        if (row.size() > numCols)
            numCols = row.size();
    }

    // expand the column data so all rows have the same number of columns
    for (auto& row : rows) {
        while (row.size() < numCols)
            row.emplace_back("");
    }

    return numCols;
}
