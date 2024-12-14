#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <cmath>
#include <climits>
#include <set>

using namespace std;

// Function to calculate the safety factor
int calculateSafetyFactor(const vector<tuple<int, int, int, int>>& robots, int width, int height) {
    const int TIME = 100;

    // Calculate middle dividing lines
    int midX = width / 2;   // Middle column (rounded down)
    int midY = height / 2;  // Middle row (rounded down)

    // Quadrant counts
    int countQ1 = 0, countQ2 = 0, countQ3 = 0, countQ4 = 0;

    // Simulate the motion of each robot
    for (const auto& robot : robots) {
        int px, py, vx, vy;
        tie(px, py, vx, vy) = robot;

        // Calculate new position after 100 seconds (with wrap-around)
        int x_new = (px + TIME * vx) % width;
        if (x_new < 0) x_new += width; // Handle negative modulo
        int y_new = (py + TIME * vy) % height;
        if (y_new < 0) y_new += height; // Handle negative modulo

        // Determine the quadrant (skip robots on the middle lines)
        if (x_new == midX || y_new == midY) continue; // Robots on the middle lines are ignored
        if (x_new > midX && y_new < midY) countQ1++;  // Q1: Top-right
        else if (x_new < midX && y_new < midY) countQ2++; // Q2: Top-left
        else if (x_new < midX && y_new > midY) countQ3++; // Q3: Bottom-left
        else if (x_new > midX && y_new > midY) countQ4++; // Q4: Bottom-right
    }

    // Debugging output to verify counts
    cout << "countQ1: " << countQ1 << ", countQ2: " << countQ2
         << ", countQ3: " << countQ3 << ", countQ4: " << countQ4 << endl;

    // Compute the safety factor
    return countQ1 * countQ2 * countQ3 * countQ4;
}

// Function to simulate robot movements and find the Christmas tree pattern
int findChristmasTree(vector<tuple<int, int, int, int>> robots, int width, int height) {
    for (int seconds = 1; seconds <= 10000; seconds++) {
        // Use a set to track robot positions
        set<pair<int, int>> positions;

        // Update positions
        for (auto& robot : robots) {
            int px, py, vx, vy;
            tie(px, py, vx, vy) = robot;

            // Update position
            px = (px + vx) % width;
            if (px < 0) px += width; // Handle negative modulo
            py = (py + vy) % height;
            if (py < 0) py += height; // Handle negative modulo

            // Store updated position
            positions.emplace(px, py);

            // Update robot position
            robot = make_tuple(px, py, vx, vy);
        }

        // Check for the Christmas tree pattern
        // Horizontal lines of 25 robots
        int horizontalLines = 0;
        for (int y = 0; y < height; y++) {
            int count = 0;
            for (int x = 0; x < width; x++) {
                if (positions.count({x, y})) {
                    count++;
                    if (count == 20) {
                        horizontalLines++;
                        break;
                    }
                } else {
                    count = 0;
                }
            }
        }

        // Vertical lines of 25 robots
        int verticalLines = 0;
        for (int x = 0; x < width; x++) {
            int count = 0;
            for (int y = 0; y < height; y++) {
                if (positions.count({x, y})) {
                    count++;
                    if (count == 20) {
                        verticalLines++;
                        break;
                    }
                } else {
                    count = 0;
                }
            }
        }

        // If we have 2 horizontal lines and 3 vertical lines, print the grid and return the time
        if (horizontalLines >= 2 && verticalLines >= 3) {
            // Print the grid
            cout << "Grid at time " << seconds << ":\n";
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    if (positions.count({x, y})) {
                        cout << 'x';
                    } else {
                        cout << '-';
                    }
                }
                cout << '\n';
            }
            return seconds;
        }
    }

    // Return -1 if no match is found within 10,000 seconds
    return -1;
}

// Function to read robots from a file
vector<tuple<int, int, int, int>> readRobotsFromFile(const string& filename) {
    vector<tuple<int, int, int, int>> robots;
    ifstream infile(filename);

    if (!infile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(infile, line)) {
        // Parse a line of the form "p=x,y v=x,y"
        int px, py, vx, vy;
        char ignore;
        stringstream ss(line);
        ss >> ignore >> ignore >> px >> ignore >> py >> ignore >> ignore >> vx >> ignore >> vy;
        robots.emplace_back(px, py, vx, vy);
    }

    infile.close();
    return robots;
}

int main() {

    // Parse command-line arguments
    string inputFile = "sample_input.txt";
    int width = 11;
    int height = 7;

    // Read robots from the input file
    vector<tuple<int, int, int, int>> sample_robots = readRobotsFromFile(inputFile);

    // Calculate the safety factor
    int sample_safetyFactor = calculateSafetyFactor(sample_robots, width, height);
    cout << "Safety Factor sample: " << sample_safetyFactor << endl;


    // Parse command-line arguments
    inputFile = "input.txt";
    width = 101;
    height = 103;

    // Read robots from the input file
    vector<tuple<int, int, int, int>> robots = readRobotsFromFile(inputFile);

    // Calculate the safety factor
    int safetyFactor = calculateSafetyFactor(robots, width, height);
    cout << "Safety Factor: " << safetyFactor << endl;

    // Find the fewest seconds for the Christmas tree pattern
    int time = findChristmasTree(robots, width, height);
    if (time != -1) {
        cout << "The fewest seconds for the Christmas tree pattern: " << time << endl;
    } else {
        cout << "No Christmas tree pattern found within 10,000 seconds." << endl;
    }

    return 0;
}
