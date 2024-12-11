#ifndef NUMBERPROCESSOR_H
#define NUMBERPROCESSOR_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <queue>


class NumberProcessor {
private:
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<int>> parseMap(const std::vector<std::string>& input);
    std::vector<std::pair<int, int>> findTrailheads(const std::vector<std::vector<int>>& grid);
    int bfsTrailhead(const std::vector<std::vector<int>>& grid, std::pair<int, int> start);

public:
    bool readInput(const std::string& fileName);
    int calculateTrailheadScores();
    int calculateTrailheadRatings();
    int dfsTrailhead(const std::vector<std::vector<int>>& grid, int x, int y, std::set<std::pair<int, int>>& visited);

};

#endif // NUMBERPROCESSOR_H
