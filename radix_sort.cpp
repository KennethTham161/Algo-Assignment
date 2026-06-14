// *********************************************************
// Program: radix_sort.cpp
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
// Member_2: Radix sort programs (implement radixSort below)
// Member_3: Heap sort programs
// Member_4: Hash table search programs
// *********************************************************
//
// FILE GUIDE
// [SCAFFOLD]  = already done by group leader. Do not change unless fixing a bug.
// [MEMBER 2]  = YOUR WORK. Write your full radix sort code here.
//
// What Member 2 must implement:
//   - radixSort()
//
// What is already done for you:
//   - Reading CSV input
//   - Timing the sort (I/O excluded)
//   - Writing sorted CSV output
//   - Printing running time to console
//
// Tip: reuse the same radix sort logic from radix_sort_step.cpp,
//      but without writing step lines.

#include "common.h"

#include <chrono>
#include <fstream>
#include <iostream>

using namespace std;

// ============================================================================
// [MEMBER 2] IMPLEMENT HERE
// Function: radixSort
//
// Your job:
//   1. Sort the whole vector "data" using LSD radix sort (by integer key only).
//   2. Process digits from right to left: d = 10 down to 1.
//   3. Use counting sort for each digit pass.
//   4. Do NOT use sort(), qsort(), or any library sorting function.
//   5. No step logging needed here (only sort the data).
// ============================================================================
void radixSort(vector<Record> &data) {

    // ----- START PLACEHOLDER (Member 2: delete this line when done) -----
    cout << "TODO: Implement radixSort() in radix_sort.cpp" << endl;
    // ----- END PLACEHOLDER -----

    // ----- START MEMBER 2 IMPLEMENTATION -----
    //
    // Write your full radix sort code here.
    //
    // ----- END MEMBER 2 IMPLEMENTATION -----
}

// ============================================================================
// [SCAFFOLD] main() - already done by group leader
// Reads input, times your radixSort(), writes output, prints running time.
// Member 2 may only change the input settings block if tutor asks during demo.
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

    auto startTime = chrono::high_resolution_clock::now();

    radixSort(data);

    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = endTime - startTime;
    double seconds = elapsed.count();

    long datasetSize = getDatasetSizeFromFilename(inputFile);
    if (datasetSize < 0) {
        datasetSize = (long)data.size();
    }

    string outputFile = "radix_sorted_dataset_" + to_string(datasetSize) + ".csv";
    writeCsv(outputFile, data);

    cout << "Radix sort completed." << endl;
    cout << "Input file: " << inputFile << endl;
    cout << "Output file: " << outputFile << endl;
    cout << "Running time: " << seconds << " seconds" << endl;

    return 0;
}
