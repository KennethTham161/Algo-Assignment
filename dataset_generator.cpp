// *********************************************************
// Program: dataset_generator.cpp
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
// Member_1: Dataset generator (fully implemented)
// Member_2: Radix sort programs
// Member_3: Heap sort programs
// Member_4: Hash table search programs
// *********************************************************
//
// [MEMBER 1 - COMPLETE] This file is fully implemented by the group leader.
// Other members do not need to change this file.
//
// Generates dataset_n.csv with unique 10-digit integers and 5-letter strings.

#include "common.h"

#include <iostream>
#include <random>
#include <set>

using namespace std;

string randomString(mt19937_64 &rng) {
    string result = "";
    uniform_int_distribution<int> letterDist('a', 'z');

    for (int i = 0; i < 5; i++) {
        result += (char)letterDist(rng);
    }

    return result;
}

int main(int argc, char *argv[]) {
    mt19937_64 rng(2431324546ULL);

    long n = 1000;

    if (argc >= 2) {
        n = stol(argv[1]);
    } else {
        cout << "Usage: dataset_generator <size n>" << endl;
        cout << "No size given. Using default n = 1000." << endl;
    }

    if (n <= 0) {
        cerr << "Error: size n must be positive." << endl;
        return 1;
    }

    const unsigned long long MIN_KEY = 1000000000ULL;
    const unsigned long long MAX_KEY = 9999999999ULL;

    vector<Record> data;
    set<unsigned long long> usedKeys;
    uniform_int_distribution<unsigned long long> keyDist(MIN_KEY, MAX_KEY);

    cout << "Generating " << n << " unique records..." << endl;

    while ((long)data.size() < n) {
        unsigned long long key = keyDist(rng);

        if (usedKeys.count(key) > 0) {
            continue;
        }

        usedKeys.insert(key);

        Record record;
        record.key = key;
        record.str = randomString(rng);
        data.push_back(record);
    }

    string outputFile = "dataset_" + to_string(n) + ".csv";
    writeCsv(outputFile, data);

    cout << "Done." << endl;
    cout << "Created file: " << outputFile << endl;
    cout << "Total records: " << data.size() << endl;

    return 0;
}
