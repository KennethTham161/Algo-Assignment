// *********************************************************
// Program: hash_table_search_step.cpp
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC4L
// Tutorial Class: T13L
// Trimester: 2610
// Member_1: 243UC245NP | KENNETH THAM YU JIANG (leader) | KENNETH.THAM.YU@student.mmu.edu.my | 01127561380
// Member_2: ID | NAME | EMAIL | PHONE
// Member_3: ID | NAME | EMAIL | PHONE
// Member_4: 242UC244PQ | MUHAMMAD SYAZRIN MUHAIMIN BIN ZAIFUL AZRAI | muhammad.syazrin.muhaimin@student.mmu.edu.my | 0194870904
// *********************************************************
// Task Distribution
// Member_1: Dataset generator
// Member_2: Radix sort programs
// Member_3: Heap sort programs
// Member_4: Hash table search programs (implement below)
// *********************************************************
//
// FILE GUIDE
// [SCAFFOLD]  = already done by group leader. Do not change unless fixing a bug.
// [MEMBER 4]  = YOUR WORK. Write your hash table and search code here.
//
// What Member 4 must implement:
//   - buildHashTable()
//   - searchTargetStep()
//   - Any helper functions / data structures you need
//   - Remove the PLACEHOLDER return in searchTargetStep() when done
//
// What is already done for you:
//   - CSV reading, output file writing
//   - main() program flow
//
// Shared helpers live in common.h (readCsv, writeCsv, formatRecord, etc.)

#include "common.h"

#include <fstream>
#include <iostream>

using namespace std;

// ============================================================================
// [MEMBER 4] IMPLEMENT HERE
// Function: buildHashTable
//
// Your job:
//   1. Insert all records from "data" into your hash table.
//   2. Choose one design:
//        - direct addressing, OR
//        - chaining with AVL tree (array-based or linked-list-based)
//   3. Do NOT use map, unordered_map, or other library search containers
//      for the actual hash table logic.
//
// Tip: if you need global/table variables, declare them in this section
//      (above buildHashTable) so searchTargetStep() can use them too.
// ============================================================================

vector<vector<Record>> hashTable;
int tableSize = 0;

// Simple division method hash function: key % tableSize
int hashFunction(unsigned long long key) {
    return (int)(key % (unsigned long long)tableSize);
}

void buildHashTable(vector<Record> &data) {

    // ----- START MEMBER 4 IMPLEMENTATION -----
    tableSize = (int)data.size();
    if (tableSize < 1) {
        tableSize = 1;
    }

    hashTable.clear();
    hashTable.resize(tableSize);

    for (int i = 0; i < (int)data.size(); i++) {
        int index = hashFunction(data[i].key);
        hashTable[index].push_back(data[i]);
    }
    // ----- END MEMBER 4 IMPLEMENTATION -----
}

// ============================================================================
// [MEMBER 4] IMPLEMENT HERE
// Function: searchTargetStep
//
// Your job:
//   1. Search for one target integer key in your hash table.
//   2. Return the search path as multiple lines:
//        Non-match: "<node.key> != <target>"
//        Found:     "<target> = <node.key>/<node.str>"
//        Not found: "-1 != <target>"
// ============================================================================
vector<string> searchTargetStep(unsigned long long target) {

    // ----- START MEMBER 4 IMPLEMENTATION -----
    vector<string> pathLines;

    int index = hashFunction(target);
    vector<Record> &bucket = hashTable[index];

    bool found = false;

    // Walk down the chain in the target bucket, one by one
    for (int i = 0; i < (int)bucket.size(); i++) {
        if (bucket[i].key == target) {
            found = true;
            pathLines.push_back(to_string(target) + " = " + formatRecord(bucket[i]));
            break;
        } else {
            //record not match line
            pathLines.push_back(to_string(bucket[i].key) + " != " + to_string(target));
        }
    }

    if (!found) {
        pathLines.push_back("-1 != " + to_string(target));
    }

    return pathLines;
    // ----- END MEMBER 4 IMPLEMENTATION -----
}

// ============================================================================
// [SCAFFOLD] main() - already done by group leader
// Reads input, builds table, searches one target, writes the .txt output file.
// Member 4 may only change the input settings block if tutor asks during demo.
// ============================================================================
int main() {
    // ----- [SCAFFOLD] Input settings (tutor may change these during demo) -----
    // string inputFile = "dataset_1000.csv";
    // unsigned long long target = 2008864030;   // example: found target
    // unsigned long long target = 123456789;  // example: not-found target

    string inputFile = "dataset_1000.csv";
    //unsigned long long target = 1970365386;   // example: found target
    unsigned long long target = 123456789;  // example: not-found target
    // ----- end input settings -----

    vector<Record> data = readCsv(inputFile);

    if (data.empty()) {
        cerr << "Error: no data loaded from " << inputFile << endl;
        return 1;
    }

    buildHashTable(data);
    vector<string> pathLines = searchTargetStep(target);

    long datasetSize = getDatasetSizeFromFilename(inputFile);
    if (datasetSize < 0) {
        datasetSize = (long)data.size();
    }

    string outputFile = "dataset_" + to_string(datasetSize) +
                        "_hash_table_search_step_" + to_string(target) + ".txt";

    ofstream out(outputFile);
    if (!out.is_open()) {
        cerr << "Error: cannot create file " << outputFile << endl;
        return 1;
    }

    for (int i = 0; i < (int)pathLines.size(); i++) {
        out << pathLines[i] << endl;
    }
    out.close();

    cout << "Search step output written to: " << outputFile << endl;
    for (int i = 0; i < (int)pathLines.size(); i++) {
        cout << pathLines[i] << endl;
    }
    return 0;
}
