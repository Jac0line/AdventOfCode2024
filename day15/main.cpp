#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <unordered_map>
#include <set>
#include <array>

using namespace std;

// Define a type alias for a grid
using Grid = vector<string>;

enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// Function to parse the input file
void parseInput(const string &inputFile, Grid &grid, string &moves) {
    ifstream file(inputFile);
    if (!file) {
        cerr << "Error: Unable to open file " << inputFile << endl;
        exit(1);
    }

    string line;
    bool readingGrid = true;

    // Read the input file line by line
    while (getline(file, line)) {
        if (line.empty()) {
            readingGrid = false; // Switch to reading moves after a blank line
            continue;
        }

        if (readingGrid) {
            grid.push_back(line); // Add line to the grid
        } else {
            moves += line; // Append line to the moves string
        }
    }

    file.close();
}

void printGrid(const Grid &grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }
}

// Find the initial position of the robot
pair<int, int> findRobot(const Grid &grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '@') {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // Should not reach here
}

// Check if a position is valid (not a wall or out of bounds)
bool isValidPosition(const Grid &grid, int x, int y) {
    return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size() && grid[x][y] != '#';
}

void simulate(Grid &grid, const string &moves) {
    // Directions: up, down, left, right
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    unordered_map<char, int> moveMap = {{'^', 0}, {'v', 1}, {'<', 2}, {'>', 3}};
    
    // Find the robot's initial position
    auto [robotX, robotY] = findRobot(grid);

    // Process each move
    for (char move : moves) {
        int dir = moveMap[move];
        int newRobotX = robotX + directions[dir].first;
        int newRobotY = robotY + directions[dir].second;
        // std::cout << "dir: " << dir << ", newRobotX: " << newRobotX << ", newRobotY: " << newRobotY <<std::endl;
        // printGrid(grid);

        // Check if the robot can move
        if (isValidPosition(grid, newRobotX, newRobotY)) {
            if (grid[newRobotX][newRobotY] == 'O') { // There's a box in the way
                // Check if we can push all boxes in this direction
                vector<pair<int, int>> boxesToMove;
                int currentX = newRobotX, currentY = newRobotY;

                // Traverse in the direction to find all consecutive boxes
                while (isValidPosition(grid, currentX, currentY) && grid[currentX][currentY] == 'O') {
                    boxesToMove.emplace_back(currentX, currentY);
                    currentX += directions[dir].first;
                    currentY += directions[dir].second;
                }

                // Check if the last position is a valid empty space for the boxes to move
                if (isValidPosition(grid, currentX, currentY) && grid[currentX][currentY] == '.') {
                    // Move all boxes
                    for (int i = boxesToMove.size() - 1; i >= 0; i--) {
                        int boxX = boxesToMove[i].first;
                        int boxY = boxesToMove[i].second;
                        int newBoxX = boxX + directions[dir].first;
                        int newBoxY = boxY + directions[dir].second;

                        grid[newBoxX][newBoxY] = 'O'; // Move the box
                        grid[boxX][boxY] = '.';      // Empty the old box position
                    }
                } else {
                    // The boxes cannot be moved; robot is blocked
                    continue;
                }
            }

            // Move the robot
            grid[robotX][robotY] = '.';
            grid[newRobotX][newRobotY] = '@';
            robotX = newRobotX;
            robotY = newRobotY;
        }
    }
}


// Compute the sum of all box GPS coordinates
int computeGPS(const Grid &grid) {
    int sum = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'O') {
                sum += 100 * i + j;
            }
        }
    }
    return sum;
}

std::set<std::array<int, 2>> touching_in_dir_vertical(
    std::vector<std::string> &grid, int row, int col, int dir, bool &movable) {
    std::set<std::array<int, 2>> this_box_posns;
    if (grid[row][col] == '[') {
        this_box_posns.insert(std::array<int, 2>{{row, col}});
        this_box_posns.insert(std::array<int, 2>{{row, col + 1}}); // must be to the right
    } else if (grid[row][col] == ']') {
        this_box_posns.insert(std::array<int, 2>{{row, col}});
        this_box_posns.insert(std::array<int, 2>{{row, col - 1}});
    } else {
        if (grid[row][col] == '#') {
            movable = false;
        }
        return {};
    }

    std::set<std::array<int, 2>> temp, total_posns;
    for (const std::array<int, 2>& pos : this_box_posns) {
        if (dir == UP)
            temp = touching_in_dir_vertical(grid, pos[0] - 1, pos[1], dir, movable);
        else if (dir == DOWN)
            temp = touching_in_dir_vertical(grid, pos[0] + 1, pos[1], dir, movable);
        total_posns.insert(temp.begin(), temp.end());
    }
    total_posns.insert(this_box_posns.begin(), this_box_posns.end());
    return total_posns;
}

std::set<std::array<int, 2>> touching_in_dir_horizontal(std::vector<std::string> &grid, int row, int col, int dir, bool &movable)
{
    std::vector<std::array<int, 2>> this_box_posns;
    if (dir == LEFT) {
        for (int i=col - 1; i >= 0; i--) {
            if (grid[row][i] != '[' && grid[row][i] != ']') {
                if (grid[row][i] == '#')
                    movable = false;
                break;
            }
            this_box_posns.push_back({row, i});
        }
    } else if (dir == RIGHT) {
        for (int i=col + 1; i < grid[0].size(); i++) {
            if (grid[row][i] != '[' && grid[row][i] != ']') {
                if (grid[row][i] == '#')
                    movable = false;
                break;
            }
            this_box_posns.push_back({row, i});
        }
    }
    return std::set<std::array<int, 2>>(this_box_posns.begin(), this_box_posns.end());
}

void move(std::vector<std::string> &grid, int &row, int &col, int dir) 
{
    std::vector<std::string> grid_copy = grid;
    bool movable = true;
    int origrow = row, origcol = col;
    std::set<std::array<int, 2>> box_posns;
    if (dir == UP) {
        box_posns = touching_in_dir_vertical(grid, row - 1, col, dir, movable);
    } else if (dir == DOWN) {
        box_posns = touching_in_dir_vertical(grid, row + 1, col, dir, movable);
    } else if (dir == LEFT) {
        box_posns = touching_in_dir_horizontal(grid, row, col, dir, movable);
    } else if (dir == RIGHT) {
        box_posns = touching_in_dir_horizontal(grid, row, col, dir, movable);
    }

    grid_copy[row][col] = '.';

    if (movable) {
        if (dir == UP)
            row--;
        if (dir == DOWN)
            row++;
        if (dir == LEFT)
            col--;
        if (dir == RIGHT)
            col++;
    }

    if (movable && box_posns.size() != 0) {
        for (std::array<int, 2> pos : box_posns) {
            grid_copy[pos[0]][pos[1]] = '.';
            if (dir == UP) {
                for (std::array<int, 2> pos : box_posns) {
                    grid_copy[pos[0] - 1][pos[1]] = grid[pos[0]][pos[1]];
                }
            } else if (dir == DOWN) {
                for (std::array<int, 2> pos : box_posns) {
                    grid_copy[pos[0] + 1][pos[1]] = grid[pos[0]][pos[1]];
                }
            } else if (dir == LEFT) {
                for (std::array<int, 2> pos : box_posns) {
                    grid_copy[pos[0]][pos[1] - 1] = grid[pos[0]][pos[1]];
                }
            } else if (dir == RIGHT) {
                for (std::array<int, 2>pos : box_posns) {
                    grid_copy[pos[0]][pos[1] + 1] = grid[pos[0]][pos[1]];
                }
            }
        }
    }
    grid_copy[row][col] = '@';
    grid = grid_copy;
    // for (int i = 0; i < grid.size(); i++) {
    //     for (int j = 0; j < grid[i].size(); j++) {
    //         std::cout << grid[i][j];
    //     }
    //     std::cout << std::endl;
    // }
}

int main() {
    string inputFile = "input.txt"; // Input file name
    Grid grid;
    string moves;

    // Parse the input file
    parseInput(inputFile, grid, moves);

    // Simulate the robot's movements
    simulate(grid, moves);

    // Compute the sum of box GPS coordinates
    int result = computeGPS(grid);

    // Output the result
    cout << "Sum of GPS coordinates: " << result << endl;

    printGrid(grid);

    //clear grid to fill again for part2
    grid.clear();
    grid.resize(0);

    std::ifstream in("input.txt");
    std::string line;

    bool reached_moves = false;
    
    while (getline(in, line)) {
        if (line == "") {
            reached_moves = true;
            continue;
        }

        std::string warehouse_line;
        if (!reached_moves) {
            for (char pos : line) {
                if (pos == '#')
                    warehouse_line += "##";
                else if (pos == '.')
                    warehouse_line += "..";
                else if (pos == 'O')
                    warehouse_line += "[]";
                else if (pos == '@')
                    warehouse_line += "@.";
            }
            grid.push_back(warehouse_line);
        } else {
            moves += line;
        }
    }

    int start_rows = -1, start_cols = -1;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '@') {
                start_rows = i;
                start_cols = j;
                break;
            }
        }
        if (start_rows != -1)
            break;
    }

    for (char dir : moves) {
        if (dir == '<')
            move(grid, start_rows, start_cols, LEFT);
        if (dir == '>')
            move(grid, start_rows, start_cols, RIGHT);
        if (dir == '^')
            move(grid, start_rows, start_cols, UP);
        if (dir == 'v')
            move(grid, start_rows, start_cols, DOWN);
    }

    long long p2 = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '[') {
                p2 += 100 * i + j;
            }
        }
    }
    std::cout << "p2: " << p2 << '\n';
    printGrid(grid);

    return 0;
}
