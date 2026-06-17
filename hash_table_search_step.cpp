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

void buildHashTable(vector<Record> &data) {

    // ----- START MEMBER 4 IMPLEMENTATION -----
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = NULL;
    }

    for (int i = 0; i < (int)data.size(); i++) {
        int slot = hashKey(data[i].key);

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

    // ----- START MEMBER 4 IMPLEMENTATION -----
    int slot = hashKey(target);

    Node* current = table[slot];
    while (current != NULL) {
        if (current->key == target) {
            return to_string(target) + " = " + to_string(current->key) + "/" + current->str;
        }
        current = current->next;
    }
    return "-1 != " + to_string(target);
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
