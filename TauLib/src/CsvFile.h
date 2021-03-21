#pragma once
#include <string>
#include <map>
#include <vector>
#include "Str.h"

using CsvLine = Tau::Strings;

/// 
/// @brief CsvFile - reads a Comma Separated Value file or strings separated by commas
/// 
struct CsvFile {
    std::vector<CsvLine> data;
    size_t numRows {0};
    size_t numCols {0};   // the max in all the rows
    bool opened {false};

    CsvFile() {};
    CsvFile(const std::string& filepath) { Load(filepath); };

    bool Load(const std::string& filepath);
    void Clear();

    Tau::Strings GetRow(size_t rowIndex);
    std::string GetRowCol(size_t rowIndex, size_t colIndex);

    // finds the row a particular column string is on.  the compare is case insensitive
    std::vector<CsvLine>::iterator FindRowWithColumnValue(const std::string& str, size_t column);
};
