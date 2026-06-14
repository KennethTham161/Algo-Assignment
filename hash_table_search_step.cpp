// *********************************************************
// Program: hash_table_search_step.cpp
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC4L
// Tutorial Class: T13L
// Trimester: 2610
// Member_1: 243UC245NP | KENNETH THAM YU JIANG (leader) | KENNETH.THAM.YU@student.mmu.edu.my | 01127561380
// Member_2: ID | NAME | EMAIL | PHONE
// Member_3: ID | NAME | EMAIL | PHONE
// Member_4: ID | NAME | EMAIL | PHONE
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
void buildHashTable(vector<Record> &data) {

    // ----- START PLACEHOLDER (Member 4: delete this line when done) -----
    cout << "TODO: Implement buildHashTable() in hash_table_search_step.cpp" << endl;
    // ----- END PLACEHOLDER -----

    // ----- START MEMBER 4 IMPLEMENTATION -----
    //
    // Write your hash table build code here.
    //
    // ----- END MEMBER 4 IMPLEMENTATION -----
}

// ============================================================================
// [MEMBER 4] IMPLEMENT HERE
// Function: searchTargetStep
//
// Your job:
//   1. Search for one target integer key in your hash table.
//   2. Return the result as one string line:
//        Found:     "2008864030 = 2008864030/rdiea"
//        Not found: "-1 != 123456789"
//   3. Delete the PLACEHOLDER return below when your real code works.
// ============================================================================
string searchTargetStep(unsigned long long target) {

    // ----- START PLACEHOLDER (Member 4: delete this whole block) -----
    cout << "TODO: Implement searchTargetStep() in hash_table_search_step.cpp" << endl;
    return "-1 != " + to_string(target);
    // ----- END PLACEHOLDER -----

    // ----- START MEMBER 4 IMPLEMENTATION -----
    //
    // Write your single-target search code here.
    //
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
    unsigned long long target = 123456789;
    // ----- end input settings -----

    vector<Record> data = readCsv(inputFile);

    if (data.empty()) {
        cerr << "Error: no data loaded from " << inputFile << endl;
        return 1;
    }

    buildHashTable(data);
    string resultLine = searchTargetStep(target);

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

    out << resultLine << endl;
    out.close();

    cout << "Search step output written to: " << outputFile << endl;
    cout << resultLine << endl;
    return 0;
}
