#include "NumberProcessor.h"

bool NumberProcessor::parseInput(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return false;
    }

    std::string line;
    bool isRules = true;
    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            isRules = false;
            continue;
        }

        if (isRules) {
            int x, y;
            std::replace(line.begin(), line.end(), '|', ' ');
            std::istringstream ss(line);
            ss >> x >> y;
            orderingRules.emplace_back(x, y);
        } else {
            std::vector<int> update;
            std::replace(line.begin(), line.end(), ',', ' ');
            std::istringstream ss(line);
            int page;
            while (ss >> page) {
                update.push_back(page);
            }
            updates.push_back(update);
        }
    }

    inputFile.close();
    return true;
}

bool NumberProcessor::isValidOrder(const std::vector<int>& update, const std::unordered_map<int, std::unordered_set<int>>& ruleGraph) const {
    std::unordered_map<int, int> position;
    for (int i = 0; i < update.size(); ++i) {
        position[update[i]] = i;
    }

    for (const auto& [x, successors] : ruleGraph) {
        if (position.find(x) == position.end()) continue; // Ignore rules for missing pages
        for (int y : successors) {
            if (position.find(y) != position.end() && position[x] >= position[y]) {
                return false; // Rule violated
            }
        }
    }

    return true;
}

std::vector<int> NumberProcessor::reorderInvalidOrder(const std::vector<int>& update, const std::unordered_map<int, std::unordered_set<int>>& ruleGraph) const {
    std::map<int, int> inDegree;
    std::map<int, std::vector<int>> graph;

    // Build a graph and calculate in-degrees for this subset of pages
    for (int page : update) {
        graph[page] = {};  // Initialize
        inDegree[page] = 0;
    }

    for (int page : update) {
        if (ruleGraph.find(page) != ruleGraph.end()) {
            for (int dependent : ruleGraph.at(page)) {
                if (graph.find(dependent) != graph.end()) {
                    graph[page].push_back(dependent);
                    inDegree[dependent]++;
                }
            }
        }
    }

    // Topological sort using Kahn's algorithm
    std::queue<int> q;
    for (const auto& [page, degree] : inDegree) {
        if (degree == 0) q.push(page);
    }

    std::vector<int> sorted;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        sorted.push_back(curr);

        for (int neighbor : graph[curr]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) q.push(neighbor);
        }
    }

    return sorted;
}

void NumberProcessor::validateUpdates() {
    // Initialize sums
    sumMiddlePages = 0;
    sumMiddlePagesIvalid = 0;

    // Build rule graph
    std::unordered_map<int, std::unordered_set<int>> ruleGraph;
    for (const auto& [x, y] : orderingRules) {
        ruleGraph[x].insert(y);
    }

    for (const auto& update : updates) {
        if (isValidOrder(update, ruleGraph)) {
            int middlePage = update[update.size() / 2];
            sumMiddlePages += middlePage;
        } else {
            std::vector<int> reordered = reorderInvalidOrder(update, ruleGraph);
            int middlePage = reordered[reordered.size() / 2];
            sumMiddlePagesIvalid += middlePage;
        }
    }
}

int NumberProcessor::getSumMiddlePages() {
    return sumMiddlePages;
}

int NumberProcessor::getSumMiddlePagesIvalid() {
    return sumMiddlePagesIvalid;
}
