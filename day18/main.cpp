#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

// Grid size for the real problem (0 to 70)
const int GRID_SIZE = 71;

// Directions for moving in the grid (right, down, left, up)
const vector<pair<int, int>> directions = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}
};

// Function to check if a cell is valid and not corrupted
bool isValid(int x, int y, const vector<vector<bool>>& grid) {
    return x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && !grid[x][y];
}

// Function to parse input file and return falling byte coordinates
vector<pair<int, int>> parseInputFile(const string& filename, bool allFallingBytes) {
    vector<pair<int, int>> fallingBytes;
    ifstream inputFile(filename);
    string line;
    if(allFallingBytes == true)
    {
        while (getline(inputFile, line) ) {
            stringstream ss(line);
            int x, y;
            char comma;
            ss >> x >> comma >> y;
            fallingBytes.emplace_back(x, y);
        }
    }
    else
    {
        while (getline(inputFile, line) && fallingBytes.size() < 1024) {
            stringstream ss(line);
            int x, y;
            char comma;
            ss >> x >> comma >> y;
            fallingBytes.emplace_back(x, y);
        }        
    }
    inputFile.close();
    return fallingBytes;
}

// Breadth-First Search (BFS) to find the shortest path
int findShortestPath(const vector<vector<bool>>& grid) {
    queue<pair<int, int>> q; // Queue to store (x, y) positions
    vector<vector<int>> steps(GRID_SIZE, vector<int>(GRID_SIZE, -1)); // Steps to each cell
    q.push({0, 0});
    steps[0][0] = 0;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        // If we've reached the bottom-right corner, return the steps
        if (x == GRID_SIZE - 1 && y == GRID_SIZE - 1) {
            return steps[x][y];
        }

        // Explore all four directions
        for (auto [dx, dy] : directions) {
            int nx = x + dx, ny = y + dy;
            if (isValid(nx, ny, grid) && steps[nx][ny] == -1) {
                steps[nx][ny] = steps[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    // If no path is found, return -1
    return -1;
}

int main() {
    // Input file containing corrupted byte coordinates
    string filename = "input.txt";

    std::cout << "------------ Part 1 ------------" << std::endl;
    // Parse the input file
    vector<pair<int, int>> fallingBytes = parseInputFile(filename, false);

    // Initialize the memory grid (false means uncorrupted)
    vector<vector<bool>> grid(GRID_SIZE, vector<bool>(GRID_SIZE, false));

        // Mark corrupted cells as bytes fall
    for (int i = 0; i < fallingBytes.size() && i < 1024; ++i) {
        int x = fallingBytes[i].first;
        int y = fallingBytes[i].second;
        if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
            grid[x][y] = true; // Mark cell as corrupted
        }
    }

    // Find the shortest path from (0, 0) to (70, 70)
    int shortestPath = findShortestPath(grid);

    // Output the result
    if (shortestPath != -1) {
        cout << "The shortest path to the exit is: " << shortestPath << " steps" << endl;
    } else {
        cout << "No path to the exit exists!" << endl;
    }

    std::cout << "------------ Part 2 ------------" << std::endl;
    //reset grid to false and clear and fill fallingBytes
    for (auto& row : grid) {
        fill(row.begin(), row.end(), false);
    }
    fallingBytes.clear();
    fallingBytes = parseInputFile(filename, true);

    int coordinateCounter = 0;
    shortestPath = findShortestPath(grid);
    while(shortestPath != -1 && coordinateCounter < fallingBytes.size())
    {
        int x = fallingBytes[coordinateCounter].first;
        int y = fallingBytes[coordinateCounter].second;
        grid[x][y] = true;
        int shortestPath = findShortestPath(grid);
        coordinateCounter++;
        
        if(shortestPath == -1)
        {
            std::cout << "Blocking coordinate: " << x << "," << y << std::endl;
            break;
        }
    }
    return 0;
}
