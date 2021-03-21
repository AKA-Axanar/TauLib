#pragma once
#include <string>
#include <map>
#include <vector>
#include "Str.h"

/// 
/// @brief CsvFile - reads a Comma Separated Value file or strings separated by commas
/// 
struct CsvFile {
    using CsvLine = std::vector<std::string>;

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
};
