// *********************************************************
// Program: hash_table_search.cpp
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC4L
// Tutorial Class: T13L
// Trimester: 2610
// Member_1: 243UC245NP | KENNETH THAM YU JIANG (leader) | KENNETH.THAM.YU@student.mmu.edu.my | 01127561380
// Member_2: ID | NAME | EMAIL | PHONE
// Member_3: ID | NAME | EMAIL | PHONE
// Member_4: 242UC244PQ | MUHAMMAD SYAZRIN MUHAIMIN BIN ZAIFUL AZRAI | MUHAMMAD.SYAZRIN.MUHAIMIN@student.mmu.edu.my | 0194870904
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

vector<vector<Record>> hashTable;
int tableSize = 0;

// Simple division method hash function: key % tableSize
int hashFunction(unsigned long long key) {
    return (int)(key % (unsigned long long)tableSize);
}

// Walks down the chain in the target bucket, one by one, return true if found
bool hashSearch(unsigned long long target, int &comparisons) {
    int index = hashFunction(target);
    vector<Record> &bucket = hashTable[index];

    comparisons = 0;
    for (int i = 0; i <(int)bucket.size(); i++) {
        comparisons++;
        if (bucket[i].key == target) {
            return true;
        }
    }
    return false;
}

void buildHashTable(vector<Record> &data) {

    // ----- START MEMBER 4 IMPLEMENTATION -----
    //Initialize all the bucket to empty
    //Table size = number of records
    tableSize = (int)data.size();
    if (tableSize < 1) {
        tableSize = 1;
    }

    hashTable.clear();
    hashTable.resize(tableSize);

    //Insert every recor into its bucket
    for (int i = 0; i < (int)data.size(); i++) {
        int index = hashFunction(data[i].key);
        hashTable[index].push_back(data[i]);
    }

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

    // ----- START MEMBER 4 IMPLEMENTATION -----
    int n = (int)data.size();

    //Find Best Case key
    unsigned long long bestKey = data[0].key;
    for (int i = 0; i < tableSize; i++) {
        if (hashTable[i].size() == 1) {
            bestKey = hashTable[i][0].key;
            break;
        }
    }

    //Find Average Case keys
    unsigned long long averageKey = data[n / 2].key;
    for (int i = 0; i < tableSize; i++) {
        if (hashTable[i].size() == 2) {
            averageKey = hashTable[i][1].key;
            break;
        }
    }

    //Find Worst Case key
    int longestIndex = 0;
    int longestSize = 0;
    for (int i = 0; i < tableSize; i++) {
        if ((int)hashTable[i].size() > longestSize) {
            longestSize = (int)hashTable[i].size();
            longestIndex = i;
        }
    }
    unsigned long long worstKey = data[n - 1].key;
    if (longestSize > 0) {
        worstKey = hashTable[longestIndex][longestSize - 1].key;
    }

    //Suggested cases:
    int comparisons = 0;
    long totalComparisons = 0;

    //Best Case
    auto startBest = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        hashSearch(bestKey, comparisons);
        totalComparisons += comparisons;
    }
    auto endBest = chrono::high_resolution_clock::now();
    bestTime = chrono::duration<double>(endBest - startBest).count();

    //Average Case
    auto startAverage = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        hashSearch(averageKey, comparisons);
        totalComparisons += comparisons;
    }
    auto endAverage = chrono::high_resolution_clock::now();
    averageTime = chrono::duration<double>(endAverage - startAverage).count();

    //Worst Case
    auto startWorst = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        hashSearch(worstKey, comparisons);
        totalComparisons += comparisons;
    }
    auto endWorst = chrono::high_resolution_clock::now();
    worstTime = chrono::duration<double>(endWorst - startWorst).count();

    cout << "(sanity check) Total comparisons: " << totalComparisons << endl;
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
