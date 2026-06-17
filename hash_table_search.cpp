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
struct Node {
    unsigned long long key;
    string str;
    Node* next;
};

static const int TABLE_SIZE = 1000003;
static Node* table[TABLE_SIZE];

int hashKey(unsigned long long key) {
    return (int)(key % (unsigned long long)TABLE_SIZE);
}

Node* chainSearch(unsigned long long key) {
    int slot = hashKey(key);
    Node* current = table[slot];
    while (current != NULL) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void buildHashTable(vector<Record> &data) {

    // ----- START MEMBER 4 IMPLEMENTATION -----
    //Initialize all the bucket to empty
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = NULL;
    }

    //Insert all the record into its bucket
    for (int i = 0; i < (int)data.size(); i++) {
        int slot = hashKey(data[i].key);

        //Create a new node and insert at the fromt of the chain
        Node* newNode = new Node();
        newNode->key = data[i].key;
        newNode->str = data[i].str;
        newNode->next = table[slot];
        table[slot] = newNode;
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

    vector<int> bucketSize(TABLE_SIZE, 0);
    for (int i = 0; i < n; i++) {
        bucketSize[hashKey(data[i].key)]++;
    }

    //Best case
    vector<unsigned long long> bestKeys;
    for (int i = 0; i < n && (int)bestKeys.size() < n; i++) {
        if (bucketSize[hashKey(data[i].key)] == 1) 
            bestKeys.push_back(data[i].key);
    
    }

    //Fill up to n if not enough size -1 buckets
    for (int i = 0; i < n && (int)bestKeys.size() < n; i++)
        bestKeys.push_back(data[i].key);

    //Average case
    vector<unsigned long long> avgKeys;
    for (int i = 0; i < n; i++) 
        avgKeys.push_back(data[i].key);
    

    //Worst case
    int worstSlot = 0;
    for (int i = 1; i < TABLE_SIZE; i++)
        if (bucketSize[i] > bucketSize[worstSlot]) 
            worstSlot = i;

    vector<unsigned long long> worstBucketKeys;
    for (int i = 0; i < n; i++)
        if (hashKey(data[i].key) == worstSlot)
            worstBucketKeys.push_back(data[i].key);
    if (worstBucketKeys.empty())
        worstBucketKeys = avgKeys;

    //Repeat worst bucket keya until we have n searches
    vector<unsigned long long> worstKeys;
    for (int i = 0; (int)worstKeys.size() < n; i++)
        worstKeys.push_back(worstBucketKeys[i % (int)worstBucketKeys.size()]);

    //Time best case (n searches)
    volatile int dummy = 0;
    auto t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) 
        dummy += (chainSearch(bestKeys[i]) != NULL) ? 1 : 0;
    auto t2 = chrono::high_resolution_clock::now();
    bestTime = chrono::duration<double>(t2 - t1).count();

    //Time average case (n searches)
    auto t3 = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
        dummy += (chainSearch(avgKeys[i]) != NULL) ? 1 : 0;
    auto t4 = chrono::high_resolution_clock::now();
    averageTime = chrono::duration<double>(t4 - t3).count();

    //Time worst case (n searches)
    auto t5 = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
        dummy += (chainSearch(worstKeys[i]) != NULL) ? 1 : 0;
    auto t6 = chrono::high_resolution_clock::now();
    worstTime = chrono::duration<double>(t6 - t5).count();

    if (dummy == 0) { cout << ""; }
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
