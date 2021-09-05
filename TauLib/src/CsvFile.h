#pragma once
///
/// @file
/// @brief Header file for CsvFile class.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

#include <string>
#include <map>
#include <vector>
#include "Str.h"

using Tau::Strings;

/// 
/// @brief CsvFile - reads a CSV (Comma Separated Values) file
/// 
struct CsvFile {
    std::string csvFilePath;
    std::vector<Strings> rows;
    bool opened {false};

    CsvFile() {};
    CsvFile(const std::string& filepath) { Load(filepath); };

    bool Load(const std::string& filepath);
    bool ReLoad();
    void Clear();
    bool SaveAs(const std:: string& filepath);
    bool Save();

    void AddString(const std::string& line);    // add a string of comma separated values
    bool AddRow(const Strings& row);            // add a row of strings
    void RemoveRow(unsigned int rowIndex);
    bool RemoveRow(const Tau::Strings& searchItems);    // remove the row where the first items in the row match the passed searchItems
    void Sort(unsigned int column = 0);

    // finds the first row where the passed rowItems match the first items in the row.
    // it does not fail if there are more items in the row than being passed.
    // returns the index of the first row that matches.  returns -1 if a row was not found with those items.
    int FindRow(const Tau::Strings& searchItems);

    // returns true if the passed items exist at the front of a row
    bool Found(const Tau::Strings& searchItems);

    // find the max number of columns used and expand all rows to that size.
    // returns the number of columns
    size_t ExpandToSameNumberOfColumns();
};
