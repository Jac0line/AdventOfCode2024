#include "NumberProcessor.h"

std::vector<std::vector<int>> NumberProcessor::parseMap(const std::vector<std::string>& input) {
    std::vector<std::vector<int>> grid;
    for (const std::string& line : input) {
        std::vector<int> row;
        for (char c : line) {
            row.push_back(c - '0'); // Convert char to integer
        }
        grid.push_back(row);
    }
    return grid;
}

bool NumberProcessor::readInput(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return false;
    }
    std::string line;
    std::vector<std::string> lineVector;
    while (std::getline(inputFile, line)) {
        lineVector.push_back(line);
    }
    inputFile.close();
    grid = parseMap(lineVector);
    return true;
}

// Find all trailheads (positions with height 0)
std::vector<std::pair<int, int>> NumberProcessor::findTrailheads(const std::vector<std::vector<int>>& grid) {
    std::vector<std::pair<int, int>> trailheads;
    int rows = grid.size();
    int cols = grid[0].size();

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == 0) {
                trailheads.emplace_back(r, c);
            }
        }
    }
    return trailheads;
}

// Perform BFS to calculate the score for a trailhead
int NumberProcessor::bfsTrailhead(const std::vector<std::vector<int>>& grid, std::pair<int, int> start) {
    int rows = grid.size();
    int cols = grid[0].size();
    std::queue<std::pair<int, int>> q;
    std::set<std::pair<int, int>> visited;
    std::set<std::pair<int, int>> reachable9s;

    // Add the starting position to the queue
    q.push(start);

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        // If already visited, skip
        if (visited.count({x, y})) continue;
        visited.insert({x, y});

        // If the current position has height 9, add it to reachable9s
        if (grid[x][y] == 9) {
            reachable9s.insert({x, y});
            continue;
        }

        // Explore neighbors (up, down, left, right)
        const std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (const auto& [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;

            // Check if the neighbor is within bounds and is height+1
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols &&
                grid[nx][ny] == grid[x][y] + 1) {
                q.push({nx, ny});
            }
        }
    }

    // Return the number of distinct 9-height positions reachable
    return reachable9s.size();
}

int NumberProcessor::calculateTrailheadScores() {

    // Find all trailheads
    std::vector<std::pair<int, int>> trailheads = findTrailheads(grid);

    int totalScore = 0;

    // Calculate the score for each trailhead
    for (const auto& trailhead : trailheads) {
        totalScore += bfsTrailhead(grid, trailhead);
    }

    return totalScore;
}

int NumberProcessor::dfsTrailhead(const std::vector<std::vector<int>>& grid, int x, int y, std::set<std::pair<int, int>>& visited) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Mark this cell as visited
    visited.insert({x, y});

    // Base case: if the current cell has height 9, this is one valid trail
    if (grid[x][y] == 9) {
        visited.erase({x, y}); // Backtrack before returning
        return 1;
    }

    int trailCount = 0;

    // Explore neighbors (up, down, left, right)
    const std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (const auto& [dx, dy] : directions) {
        int nx = x + dx;
        int ny = y + dy;

        // Check if the neighbor is within bounds and is valid for the trail
        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols &&
            grid[nx][ny] == grid[x][y] + 1 &&
            visited.find({nx, ny}) == visited.end()) {
            trailCount += dfsTrailhead(grid, nx, ny, visited);
        }
    }

    // Backtrack: unmark this cell
    visited.erase({x, y});

    return trailCount;
}


int NumberProcessor::calculateTrailheadRatings() {
    // Find all trailheads
    std::vector<std::pair<int, int>> trailheads = findTrailheads(grid);

    int totalRating = 0;

    // Calculate the rating for each trailhead
    for (const auto& trailhead : trailheads) {
        std::set<std::pair<int, int>> visited; // Track visited cells to avoid revisiting
        totalRating += dfsTrailhead(grid, trailhead.first, trailhead.second, visited);
    }

    return totalRating;
}



