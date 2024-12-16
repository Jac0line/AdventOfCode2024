#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <tuple>
#include <map>
#include <queue>
#include <set>
#include <climits>

using namespace std;

class Solution {
private:
    vector<string> grid;
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    pair<int, int> start;
    pair<int, int> end;
    map<tuple<int, int, int>, int> dist;
    map<tuple<int, int, int>, vector<tuple<int, int, int>>> predecessors;

    void parseInput(const string &filename) {
        ifstream fin(filename);
        string line;
        int r = 0;

        while (getline(fin, line)) {
            grid.push_back(line);
            for (int c = 0; c < line.size(); c++) {
                if (line[c] == 'S') start = {r, c};
                if (line[c] == 'E') end = {r, c};
            }
            ++r;
        }
    }

    int dijkstra() {
        priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, greater<>> pq;
        pq.push({0, start.first, start.second, 0});
        dist[{start.first, start.second, 0}] = 0;

        while (!pq.empty()) {
            auto [d, r, c, dir] = pq.top();
            pq.pop();

            if (grid[r][c] == 'E') {
                return d;
            }

            for (int i = 0; i < 4; ++i) {
                int nr = r + directions[i].first;
                int nc = c + directions[i].second;
                int nd = d + 1 + (i != dir ? 1000 : 0);

                if (nr < 0 || nc < 0 || nr >= grid.size() || nc >= grid[0].size() || grid[nr][nc] == '#') {
                    continue;
                }

                auto nextState = make_tuple(nr, nc, i);
                if (dist.find(nextState) == dist.end() || nd < dist[nextState]) {
                    dist[nextState] = nd;
                    pq.push({nd, nr, nc, i});
                    predecessors[nextState].clear();
                    predecessors[nextState].push_back({r, c, dir});
                } else if (nd == dist[nextState]) {
                    predecessors[nextState].push_back({r, c, dir});
                }
            }
        }
        return INT_MAX;
    }

    int backtrack() {
        set<pair<int, int>> uniqueTiles;
        queue<tuple<int, int, int>> q;
        for (int dir = 0; dir < 4; ++dir) {
            q.push({end.first, end.second, dir});
        }

        while (!q.empty()) {
            auto [r, c, dir] = q.front();
            q.pop();

            uniqueTiles.insert({r, c});
            for (const auto &pred : predecessors[{r, c, dir}]) {
                q.push(pred);
            }
        }

        return uniqueTiles.size();
    }

public:
    Solution(const string &filename) {
        parseInput(filename);
    }

    int part1() {
        return dijkstra();
    }

    int part2() {
        dijkstra();
        return backtrack();
    }
};

int main() {
    Solution test1("input.txt");
    cout << "Lowest score: " << test1.part1() << endl;
    cout << "Tiles on best paths: " << test1.part2() << endl;

    return 0;
}
