#ifndef NUMBERPROCESSOR_H
#define NUMBERPROCESSOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <cmath>
#include <climits>
#include <set>

using namespace std;


class NumberProcessor {
public:
    vector<tuple<int, int, int, int>> readRobotsFromFile(const string& filename);
    int calculateSafetyFactor(const vector<tuple<int, int, int, int>>& robots, int width, int height);
    int findChristmasTree(vector<tuple<int, int, int, int>> robots, int width, int height);

private:
    
};

#endif // NUMBERPROCESSOR_H
