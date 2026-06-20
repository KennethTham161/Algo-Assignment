#include "common.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

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
    if (data.empty()) return;

    size_t n = data.size();
    vector<Record> output(n);

    // ----- START MEMBER 2 IMPLEMENTATION -----

    for (int d = 10; d >= 1; d--) {
        int count[10] = {0};


        for (size_t i = 0; i < n; i++) {
            int digit = getDigit(data[i].key, d);
            count[digit]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (long long i = n - 1; i >= 0; i--) {
            int digit = getDigit(data[i].key, d);
            output[count[digit] - 1] = data[i];
            count[digit]--;
        }

        for (size_t i = 0; i < n; i++) {
            data[i] = output[i];
        }


        stepLines.push_back(formatArray(data) + " d=" + to_string(d));
    }
    // ----- END MEMBER 2 IMPLEMENTATION -----
}

// ============================================================================
// [SCAFFOLD] main() - already done by group leader
// Reads input rows, calls your radixSortStep(), writes the .txt output file.
// Member 2 may only change the input settings block if tutor asks during demo.
// ============================================================================
int main() {
    // ----- [SCAFFOLD] Input settings (tutor may change these during demo) -----
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
