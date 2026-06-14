// *********************************************************
// Program: radix_sort_step.cpp
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
// Member_2: Radix sort programs (implement radixSortStep below)
// Member_3: Heap sort programs
// Member_4: Hash table search programs
// *********************************************************
//
// FILE GUIDE
// [SCAFFOLD]  = already done by group leader. You can read it, but do not change it
//               unless you really need to fix a bug.
// [MEMBER 2]  = YOUR WORK. Write your radix sort step-by-step code here.
//
// What Member 2 must implement:
//   - radixSortStep()
//   - Remove the PLACEHOLDER loop inside that function when done
//
// What is already done for you:
//   - CSV reading, output file writing, step line formatting
//   - getDigit() helper
//   - main() program flow
//
// Shared helpers live in common.h (readCsv, writeCsv, formatArray, etc.)

#include "common.h"

#include <fstream>
#include <iostream>

using namespace std;

// ============================================================================
// [SCAFFOLD] Helper function - provided for Member 2
// Returns one digit from the integer key.
// Assignment notation: d = 10 is rightmost digit, d = 1 is leftmost digit.
// ============================================================================
int getDigit(unsigned long long key, int d) {
    int positionFromRight = 11 - d;
    unsigned long long divisor = 1;

    for (int i = 1; i < positionFromRight; i++) {
        divisor *= 10;
    }

    return (int)((key / divisor) % 10);
}

// ============================================================================
// [MEMBER 2] IMPLEMENT HERE
// Function: radixSortStep
//
// Your job:
//   1. Sort the vector "data" using LSD radix sort (by integer key only).
//   2. Process digits from right to left: d = 10, 9, 8, ..., 1.
//   3. Use counting sort for each digit pass.
//   4. Do NOT use sort(), qsort(), or any library sorting function.
//   5. After each digit pass, save one line into stepLines:
//        stepLines.push_back(formatArray(data) + " d=10");
//   6. Delete the PLACEHOLDER section below when your real code works.
// ============================================================================
void radixSortStep(vector<Record> &data, vector<string> &stepLines) {

    // ----- START PLACEHOLDER (Member 2: delete this whole block) -----
    cout << "TODO: Implement radixSortStep() in radix_sort_step.cpp" << endl;

    for (int d = 10; d >= 1; d--) {
        stepLines.push_back(formatArray(data) + " d=" + to_string(d));
    }
    // ----- END PLACEHOLDER -----

    // ----- START MEMBER 2 IMPLEMENTATION -----
    //
    // Write your radix sort code here.
    //
    // ----- END MEMBER 2 IMPLEMENTATION -----
}

// ============================================================================
// [SCAFFOLD] main() - already done by group leader
// Reads input rows, calls your radixSortStep(), writes the .txt output file.
// Member 2 may only change the input settings block if tutor asks during demo.
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
    stepLines.push_back(formatArray(data) + " original");

    radixSortStep(data, stepLines);

    long datasetSize = getDatasetSizeFromFilename(inputFile);
    if (datasetSize < 0) {
        datasetSize = (long)data.size();
    }

    string outputFile = "dataset_" + to_string(datasetSize) +
                        "_radix_sorted_step_" + to_string(startRow) +
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
