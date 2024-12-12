#ifndef NUMBERPROCESSOR_H
#define NUMBERPROCESSOR_H

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <tuple>
#include <map>
#include <queue>
#include <stack>
#include <array>
#include <unordered_map>
#include <stdint.h>

using namespace std;


class NumberProcessor {
public:
    NumberProcessor(string fileName);
    uint64_t part1();
    uint64_t part2();

private:
    fstream fin;
    vector<string> grid;
    map<pair<int, int>, bool> visited;
    void loadInput();
    void dfs(int r, int c, map<pair<int, int>, int> &area, int a, char ch);
    int countCorners(int r, int c, map<pair<int, int>, int> &area);
};

#endif // NUMBERPROCESSOR_H
