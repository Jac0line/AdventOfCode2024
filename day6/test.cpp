#include <bits/stdc++.h>
using namespace std;

int start_x = 0, start_y = 0, start_direction = 0;

vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

vector<vector<int>> dir(130, vector<int>(130, -1));

bool getNextCell(vector<string> &input, int x, int y, int direction)
{
    int next_x = x + directions[direction].first;
    int next_y = y + directions[direction].second;
    if (next_x < 0 || next_x >= input.size() || next_y < 0 || next_y >= input[0].size())
        return true;
    if (input[next_x][next_y] == '#')
        return false;
    return true;
}

bool simulate(vector<string> &input, int x, int y, int direction)
{
    int cnt = 1;
    while (x >= 0 && x < input.size() && y >= 0 && y < input[0].size() and cnt<10000000)
    {
        if (getNextCell(input, x, y, direction))
        {
            if (input[x][y] == 'X' and dir[x][y] == direction)
            {
                return true;
            }
            input[x][y] = 'X';
            dir[x][y] = direction;
            x += directions[direction].first;
            y += directions[direction].second;
        }
        else
        {
            direction = (direction + 1) % 4;
        }
    }
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    vector<string> input(130);
    int x, y;
    for (int i = 0; i < 130; i++)
    {
        cin >> input[i];
        for (int j = 0; j < input[i].size(); j++)
        {
            if (input[i][j] == '^')
            {
                x = i;
                y = j;
            }
        }
    }

    vector<string> copy = input;

    start_x = x, start_y = y, start_direction = 0;
    simulate(input, x, y, 0);
    
    int ans = 0;

    for (int i = 0; i < 130; i++)
    {
        for (int j = 0; j < input[i].size(); j++)
        {
            if (input[i][j] == 'X')
            {
                vector<string> temp = copy;
                temp[i][j] = '#';
                if (simulate(temp, start_x, start_y, start_direction))
                {
                    ans++;
                }
            }
        }
    }
    cout << ans << endl;
}