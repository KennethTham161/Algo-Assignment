// *********************************************************
// Program: hash_table_search.cpp
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
// [MEMBER 4]  = YOUR WORK. Write your hash table and timing experiment code here.
//
// What Member 4 must implement:
//   - buildHashTable()
//   - runSearchExperiments()
//   - Any helper functions / data structures you need
//
// What is already done for you:
//   - Reading CSV input
//   - Writing the result .txt file
//   - Printing best/average/worst times to console
//
// Tip: you can reuse the same hash table code from hash_table_search_step.cpp.

#include "common.h"

#include <chrono>
#include <fstream>
#include <iostream>

using namespace std;

// ============================================================================
// [MEMBER 4] IMPLEMENT HERE
// Function: buildHashTable
//
// Your job:
//   1. Insert all records from "data" into your hash table.
//   2. Use the same hash table design as hash_table_search_step.cpp.
//   3. Do NOT use map, unordered_map, or other library search containers
//      for the actual hash table logic.
// ============================================================================
void buildHashTable(vector<Record> &data) {

    // ----- START PLACEHOLDER (Member 4: delete this line when done) -----
    cout << "TODO: Implement buildHashTable() in hash_table_search.cpp" << endl;
    // ----- END PLACEHOLDER -----

    // ----- START MEMBER 4 IMPLEMENTATION -----
    //
    // Write your hash table build code here.
    //
    // ----- END MEMBER 4 IMPLEMENTATION -----
}

// ============================================================================
// [MEMBER 4] IMPLEMENT HERE
// Function: runSearchExperiments
//
// Your job:
//   1. Perform n searches, where n = dataset size.
//   2. Measure and store:
//        bestTime     = fastest case (seconds)
//        averageTime  = average case (seconds)
//        worstTime    = slowest case (seconds)
//   3. Suggested cases:
//        best    = keys that are found immediately / shortest path
//        average = search keys from dataset in random order
//        worst   = keys that cause longest search path
//   4. Delete the PLACEHOLDER assignments below when your real code works.
// ============================================================================
void runSearchExperiments(vector<Record> &data,
                          double &bestTime,
                          double &averageTime,
                          double &worstTime) {

    // ----- START PLACEHOLDER (Member 4: delete this whole block) -----
    cout << "TODO: Implement runSearchExperiments() in hash_table_search.cpp" << endl;

    bestTime = 0.0;
    averageTime = 0.0;
    worstTime = 0.0;
    // ----- END PLACEHOLDER -----

    // ----- START MEMBER 4 IMPLEMENTATION -----
    //
    // Write your n-search timing experiment code here.
    //
    // ----- END MEMBER 4 IMPLEMENTATION -----
}

// ============================================================================
// [SCAFFOLD] main() - already done by group leader
// Reads input, builds table, runs your experiment, writes output file.
// Member 4 may only change the input settings block if tutor asks during demo.
// ============================================================================
int main() {
    // ----- [SCAFFOLD] Input settings (tutor may change these during demo) -----
    // string inputFile = "dataset_1000000.csv";

    string inputFile = "dataset_1000000.csv";
    // ----- end input settings -----

    vector<Record> data = readCsv(inputFile);

    if (data.empty()) {
        cerr << "Error: no data loaded from " << inputFile << endl;
        return 1;
    }

    buildHashTable(data);

    double bestTime = 0.0;
    double averageTime = 0.0;
    double worstTime = 0.0;

    auto startTime = chrono::high_resolution_clock::now();

    runSearchExperiments(data, bestTime, averageTime, worstTime);

    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = endTime - startTime;

    long datasetSize = getDatasetSizeFromFilename(inputFile);
    if (datasetSize < 0) {
        datasetSize = (long)data.size();
    }

    string outputFile = "hash_table_search_dataset_" + to_string(datasetSize) + ".txt";

    ofstream out(outputFile);
    if (!out.is_open()) {
        cerr << "Error: cannot create file " << outputFile << endl;
        return 1;
    }

    out << "Best case time: " << bestTime << " seconds" << endl;
    out << "Average case time: " << averageTime << " seconds" << endl;
    out << "Worst case time: " << worstTime << " seconds" << endl;
    out << "Total experiment time: " << elapsed.count() << " seconds" << endl;
    out.close();

    cout << "Hash table search experiment completed." << endl;
    cout << "Input file: " << inputFile << endl;
    cout << "Output file: " << outputFile << endl;
    cout << "Best case time: " << bestTime << " seconds" << endl;
    cout << "Average case time: " << averageTime << " seconds" << endl;
    cout << "Worst case time: " << worstTime << " seconds" << endl;

    return 0;
}
