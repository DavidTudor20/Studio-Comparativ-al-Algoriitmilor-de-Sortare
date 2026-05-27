#pragma once
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

inline vector<int> generateRandom(int size) {
    vector<int> vec(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 1000000);
    for (int i = 0; i < size; ++i) vec[i] = dist(gen);
    return vec;
}

inline vector<int> generateSorted(int size) {
    vector<int> vec = generateRandom(size);
    sort(vec.begin(), vec.end());
    return vec;
}

inline vector<int> generateReverseSorted(int size) {
    vector<int> vec = generateRandom(size);
    sort(vec.rbegin(), vec.rend());
    return vec;
}

inline vector<int> generateAlmostSorted(int size) {
    vector<int> vec = generateSorted(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, size - 1);
    
    int swaps = max(1, size / 20); 
    for (int i = 0; i < swaps; i++) {
        swap(vec[dist(gen)], vec[dist(gen)]);
    }
    return vec;
}

inline vector<int> generateFlat(int size) {
    vector<int> vec(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 3); 
    for (int i = 0; i < size; ++i) vec[i] = dist(gen);
    return vec;
}