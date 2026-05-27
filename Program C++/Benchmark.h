#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include "Algorithm.h" 
#include "Generators.h"

using namespace std;
using namespace chrono;

template <typename Func>
inline double measureAverageTime(Func sortFunc, const vector<int>& baseData, int runs) {
    long long totalDuration = 0;
    for (int i = 0; i < runs; i++) {
        vector<int> dataCopy = baseData;
        auto start = high_resolution_clock::now();
        sortFunc(dataCopy);
        auto end = high_resolution_clock::now();
        totalDuration += duration_cast<microseconds>(end - start).count();
    }
    return static_cast<double>(totalDuration) / runs;
}

inline void runBenchmarks(int choice) {
    ofstream outFile("advanced_benchmark.csv");
    
    outFile << "Distribution,Size,Runs,Bubble (us),Selection (us),Insertion (us),Merge (us),Quick (us)\n";

    
    vector<int> sizes = {10, 50, 100, 1000, 5000, 10000}; 
    
    vector<pair<string, vector<int>(*)(int)>> distributions = {
        {"Random", generateRandom},
        {"Sorted", generateSorted},
        {"Reverse_Sorted", generateReverseSorted},
        {"Almost_Sorted", generateAlmostSorted},
        {"Flat", generateFlat}
    };

    for (const auto& dist : distributions) {
        cout << "\n--- Testing Distribution: " << dist.first << " ---\n";

        for (int size : sizes) {
            int runs = (size <= 100) ? 50000 : 10; 
            vector<int> data = dist.second(size);

            
            double timeBubble = 0, timeSelect = 0, timeInsert = 0, timeMerge = 0, timeQuick = 0;

            cout << "Size " << setw(6) << size << " | Runs: " << setw(5) << runs << " | ";

            
            if (choice == 1 || choice == 6) {
                timeBubble = measureAverageTime(bubbleSort, data, runs);
                cout << "Bubble: " << setw(8) << timeBubble << "us ";
            }
            if (choice == 2 || choice == 6) {
                timeSelect = measureAverageTime(selectionSort, data, runs);
                cout << "Select: " << setw(8) << timeSelect << "us ";
            }
            if (choice == 3 || choice == 6) {
                timeInsert = measureAverageTime(insertionSort, data, runs);
                cout << "Insert: " << setw(8) << timeInsert << "us ";
            }
            if (choice == 4 || choice == 6) {
                timeMerge = measureAverageTime(mergeSort, data, runs);
                cout << "Merge: " << setw(8) << timeMerge << "us ";
            }
            
            if (choice == 5 || choice == 6) {
                timeQuick = measureAverageTime(quickSort, data, runs);
                cout << "Quick: " << setw(8) << timeQuick << "us ";
            }
            
            cout << "\n";

            
            outFile << dist.first << "," << size << "," << runs << "," 
                    << timeBubble << "," << timeSelect << "," 
                    << timeInsert << "," << timeMerge << "," << timeQuick << "\n";
        }
    }
    outFile.close();
    cout << "\n[!] Benchmark complete. Data saved to 'advanced_benchmark.csv'\n";
}
