#ifndef NUMBERPROCESSOR_H
#define NUMBERPROCESSOR_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <queue>

class NumberProcessor {
public:
    bool parseInput(const std::string& fileName);
    void validateUpdates();
    int getSumMiddlePages();
    int getSumMiddlePagesIvalid();

private:
    std::vector<std::pair<int, int>> orderingRules;
    std::vector<std::vector<int>> updates;
    int sumMiddlePagesIvalid;
    int sumMiddlePages;
    bool isValidOrder(const std::vector<int>& update, const std::unordered_map<int, std::unordered_set<int>>& ruleGraph) const;
    std::vector<int> reorderInvalidOrder(const std::vector<int>& update, const std::unordered_map<int, std::unordered_set<int>>& ruleGraph) const;
};

#endif // NUMBERPROCESSOR_H
