// *********************************************************
// Program: heap_sort_step.cpp
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
// Member_3: Heap sort programs (implement heapSortStep below)
// Member_4: Hash table search programs
// *********************************************************
//
// FILE GUIDE
// [SCAFFOLD]  = already done by group leader. Do not change unless fixing a bug.
// [MEMBER 3]  = YOUR WORK. Write your heap sort step-by-step code here.
//
// What Member 3 must implement:
//   - heapSortStep()
//   - Any helper functions you need (heapifyDown, buildMaxHeap, swap, etc.)
//   - Remove the PLACEHOLDER loop inside heapSortStep() when done
//
// What is already done for you:
//   - CSV reading, output file writing, step line formatting
//   - main() program flow
//
// Shared helpers live in common.h (readCsv, writeCsv, formatArray, etc.)

#include "common.h"

#include <fstream>
#include <iostream>

using namespace std;

// ============================================================================
// [MEMBER 3] IMPLEMENT HERE
// Function: heapSortStep
//
// Your job:
//   1. Sort the vector "data" using max-heap sort (by integer key only).
//   2. After each extraction step, save one line into stepLines:
//        stepLines.push_back(formatArray(data) + " i = 6");
//   3. Label steps as i = n, n-1, ..., 1.
//   4. Do NOT use sort(), qsort(), priority_queue, or library sorting.
//   5. Delete the PLACEHOLDER section below when your real code works.
//
// Suggested helpers to write in this section:
//   - swapRecords()
//   - heapifyDown()
//   - buildMaxHeap()
// ============================================================================
void heapSortStep(vector<Record> &data, vector<string> &stepLines) {

    // ----- START PLACEHOLDER (Member 3: delete this whole block) -----
    cout << "TODO: Implement heapSortStep() in heap_sort_step.cpp" << endl;

    int n = (int)data.size();
    for (int i = n; i >= 1; i--) {
        stepLines.push_back(formatArray(data) + " i = " + to_string(i));
    }
    // ----- END PLACEHOLDER -----

    // ----- START MEMBER 3 IMPLEMENTATION -----
    //
    // Write your heap sort step code here.
    //
    // ----- END MEMBER 3 IMPLEMENTATION -----
}

// ============================================================================
// [SCAFFOLD] main() - already done by group leader
// Reads input rows, calls your heapSortStep(), writes the .txt output file.
// Member 3 may only change the input settings block if tutor asks during demo.
// ============================================================================
int main() {
    // ----- [SCAFFOLD] Input settings (tutor may change these during demo) -----
    // string inputFile = "dataset_1000.csv";
    // long startRow = 1;
    // long endRow = 7;

    string inputFile = "dataset_1000.csv";
    long startRow = 1;
    long endRow = 7;
    // ----- end input settings -----

    vector<Record> data = readCsv(inputFile, startRow, endRow);

    if (data.empty()) {
        cerr << "Error: no data loaded from " << inputFile << endl;
        return 1;
    }

    vector<string> stepLines;
    stepLines.push_back(formatArray(data) + " initial");

    heapSortStep(data, stepLines);

    long datasetSize = getDatasetSizeFromFilename(inputFile);
    if (datasetSize < 0) {
        datasetSize = (long)data.size();
    }

    string outputFile = "dataset_" + to_string(datasetSize) +
                        "_heap_sorted_step_" + to_string(startRow) +
                        "_" + to_string(endRow) + ".txt";

    ofstream out(outputFile);
    if (!out.is_open()) {
        cerr << "Error: cannot create file " << outputFile << endl;
        return 1;
    }

    for (int i = 0; i < (int)stepLines.size(); i++) {
        out << stepLines[i] << endl;
    }
    out.close();

    cout << "Step output written to: " << outputFile << endl;
    return 0;
}
