#include "NumberProcessor.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    NumberProcessor processor;

    vector<tuple<int, int, int, int>> sample_robots = processor.readRobotsFromFile("sample_input.txt");
    int sample_safetyFactor = processor.calculateSafetyFactor(sample_robots, 11, 7);
    cout << "Safety Factor sample: " << sample_safetyFactor << endl;

    vector<tuple<int, int, int, int>> robots = processor.readRobotsFromFile("input.txt");
    int width = 101;
    int height = 103;
    int safetyFactor = processor.calculateSafetyFactor(robots, width, height);
    cout << "Safety Factor: " << safetyFactor << endl;

    int time = processor.findChristmasTree(robots, width, height);
    if (time != -1) {
        cout << "The fewest seconds for the Christmas tree pattern: " << time << endl;
    } else {
        cout << "No Christmas tree pattern found within 10,000 seconds." << endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Completed in: " << duration.count() << "ms" << std::endl;

    return 0;
}
