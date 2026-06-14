// *********************************************************
// Program: heap_sort.cpp
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
// Member_3: Heap sort programs (implement heapSort below)
// Member_4: Hash table search programs
// *********************************************************
//
// FILE GUIDE
// [SCAFFOLD]  = already done by group leader. Do not change unless fixing a bug.
// [MEMBER 3]  = YOUR WORK. Write your full heap sort code here.
//
// What Member 3 must implement:
//   - heapSort()
//   - Any helper functions you need (heapifyDown, buildMaxHeap, swap, etc.)
//
// What is already done for you:
//   - Reading CSV input
//   - Timing the sort (I/O excluded)
//   - Writing sorted CSV output
//   - Printing running time to console
//
// Tip: reuse the same heap sort logic from heap_sort_step.cpp,
//      but without writing step lines.

#include "common.h"

#include <chrono>
#include <fstream>
#include <iostream>

using namespace std;

// ============================================================================
// [MEMBER 3] IMPLEMENT HERE
// Function: heapSort
//
// Your job:
//   1. Sort the whole vector "data" using max-heap sort (by integer key only).
//   2. Do NOT use sort(), qsort(), priority_queue, or library sorting.
//   3. No step logging needed here (only sort the data).
// ============================================================================
void heapSort(vector<Record> &data) {

    // ----- START PLACEHOLDER (Member 3: delete this line when done) -----
    cout << "TODO: Implement heapSort() in heap_sort.cpp" << endl;
    // ----- END PLACEHOLDER -----

    // ----- START MEMBER 3 IMPLEMENTATION -----
    //
    // Write your full heap sort code here.
    //
    // ----- END MEMBER 3 IMPLEMENTATION -----
}

// ============================================================================
// [SCAFFOLD] main() - already done by group leader
// Reads input, times your heapSort(), writes output, prints running time.
// Member 3 may only change the input settings block if tutor asks during demo.
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

    heapSort(data);

    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = endTime - startTime;
    double seconds = elapsed.count();

    long datasetSize = getDatasetSizeFromFilename(inputFile);
    if (datasetSize < 0) {
        datasetSize = (long)data.size();
    }

    string outputFile = "heap_sorted_dataset_" + to_string(datasetSize) + ".csv";
    writeCsv(outputFile, data);

    cout << "Heap sort completed." << endl;
    cout << "Input file: " << inputFile << endl;
    cout << "Output file: " << outputFile << endl;
    cout << "Running time: " << seconds << " seconds" << endl;

    return 0;
}
