#include "NumberProcessor.h"

using namespace std;

void NumberProcessor::loadInput()
{
    string line;
    while (getline(this->fin, line))
    {
        this->grid.push_back(line);
    }
}

void NumberProcessor::dfs(int r, int c, map<pair<int, int>, int> &area, int a, char ch)
{
    if (r < 0 || r >= this->grid.size() || c < 0 || c >= this->grid[r].size())
        return;
    if (this->visited[{r, c}])
        return;

    if (this->grid[r][c] != ch)
        return;
    this->visited[{r, c}] = true;
    area[{r, c}] = a;

    dfs(r + 1, c, area, a, ch);
    dfs(r - 1, c, area, a, ch);
    dfs(r, c + 1, area, a, ch);
    dfs(r, c - 1, area, a, ch);
}

int NumberProcessor::countCorners(int r, int c, map<pair<int, int>, int> &area)
{
    int corners = 0;
    int current_grid_space = area[{r, c}];

    int top = area[{r - 1, c}];
    int bottom = area[{r + 1, c}];
    int left = area[{r, c - 1}];
    int right = area[{r, c + 1}];

    int top_left = area[{r - 1, c - 1}];
    int top_right = area[{r - 1, c + 1}];
    int bottom_left = area[{r + 1, c - 1}];
    int bottom_right = area[{r + 1, c + 1}];

    if (current_grid_space != top && current_grid_space != left) ++corners;
    if (current_grid_space != top && current_grid_space != right) ++corners;
    if (current_grid_space != bottom && current_grid_space != left) ++corners;
    if (current_grid_space != bottom && current_grid_space != right) ++corners;

    if (current_grid_space == right && current_grid_space == bottom && current_grid_space != bottom_right) ++corners;
    if (current_grid_space == left && current_grid_space == bottom && current_grid_space != bottom_left) ++corners;
    if (current_grid_space == right && current_grid_space == top && current_grid_space != top_right) ++corners;
    if (current_grid_space == left && current_grid_space == top && current_grid_space != top_left) ++corners;
    return corners;
}

NumberProcessor::NumberProcessor(string fileName)
{
    this->fin.open(fileName, ios::in);
    this->loadInput();
    this->fin.close();
}

uint64_t NumberProcessor::part1() 
{
    uint64_t sol = 0;
    map<pair<int, int>, int> area;
    map<int, pair<int, int>> sizes;

    int a = 1;
    for (int r = 0; r < this->grid.size(); r++)
    {
        for (int c = 0; c < this->grid[r].size(); c++)
        {
            if (!this->visited[{r, c}])
                dfs(r, c, area, a++, this->grid[r][c]);
        }
    }

    for (int r = 0; r < this->grid.size(); r++)
    {
        for (int c = 0; c < this->grid[r].size(); c++)
        {
            sizes[area[{r, c}]].first++;

            for (int j = 0; j < 4; ++j)
            {
                int nr = r + "0121"[j] - '1';
                int nc = c + "1210"[j] - '1';

                if (nr < 0 || nr >= this->grid.size() || nc < 0 || nc >= this->grid[r].size())
                    sizes[area[{r, c}]].second++;
                else if (area[{nr, nc}] != area[{r, c}])
                    sizes[area[{r, c}]].second++;
            }
        }
    }

    for (auto [k, v] : sizes)
        sol += v.first * v.second;

    return sol;
}

uint64_t NumberProcessor::part2() 
{
    this->visited.clear();

    uint64_t sol = 0;
    map<pair<int, int>, int> area;
    map<int, pair<int, int>> sizes;

    int a = 1;
    for (int r = 0; r < this->grid.size(); r++)
    {
        for (int c = 0; c < this->grid[r].size(); c++)
        {
            if (!this->visited[{r, c}])
                dfs(r, c, area, a++, this->grid[r][c]);
        }
    }

    for (int r = 0; r < this->grid.size(); r++)
    {
        for (int c = 0; c < this->grid[r].size(); c++)
        {
            sizes[area[{r, c}]].first++;
            sizes[area[{r, c}]].second += this->countCorners(r, c, area);
        }
    }

    for (auto [k, v] : sizes)
        sol += v.first * v.second;

    return sol;
}
