#ifndef COMMON_H
#define COMMON_H

// ============================================================================
// [SCAFFOLD] common.h - shared helpers provided by group leader (Member 1)
//
// Used by ALL 7 programs during development.
// Before final submission, paste this file into each .cpp and remove #include.
//
// Contains:
//   - Record struct
//   - readCsv / writeCsv
//   - formatRecord / formatArray (for step output files)
//   - getDatasetSizeFromFilename
//
// Team members do NOT need to modify this file for their algorithm work.
// ============================================================================

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Record {
    unsigned long long key;
    string str;
};

vector<Record> readCsv(string path, long startRow = -1, long endRow = -1) {
    vector<Record> data;
    ifstream file(path);

    if (!file.is_open()) {
        cerr << "Error: cannot open file " << path << endl;
        return data;
    }

    string line;
    long rowNumber = 0;

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        rowNumber++;

        if (startRow != -1 && rowNumber < startRow) {
            continue;
        }
        if (endRow != -1 && rowNumber > endRow) {
            break;
        }

        size_t commaPos = line.find(',');
        if (commaPos == string::npos) {
            continue;
        }

        Record record;
        record.key = stoull(line.substr(0, commaPos));
        record.str = line.substr(commaPos + 1);
        data.push_back(record);
    }

    file.close();
    return data;
}

void writeCsv(string path, vector<Record> &data) {
    ofstream file(path);

    if (!file.is_open()) {
        cerr << "Error: cannot create file " << path << endl;
        return;
    }

    for (int i = 0; i < (int)data.size(); i++) {
        file << data[i].key << "," << data[i].str << endl;
    }

    file.close();
}


string formatRecord(Record r) {
    return to_string(r.key) + "/" + r.str;
}


string formatArray(vector<Record> &data) {
    string result = "[";

    for (int i = 0; i < (int)data.size(); i++) {
        result += formatRecord(data[i]);
        if (i < (int)data.size() - 1) {
            result += ", ";
        }
    }

    result += "]";
    return result;
}

long getDatasetSizeFromFilename(string filename) {
    size_t underscorePos = filename.find('_');
    size_t dotPos = filename.find(".csv");

    if (underscorePos == string::npos || dotPos == string::npos || dotPos <= underscorePos + 1) {
        return -1;
    }

    string sizeText = filename.substr(underscorePos + 1, dotPos - underscorePos - 1);
    return stol(sizeText);
}

#endif
