#include <bits/stdc++.h>
using namespace std;

void solve_case()
{
    int R, C; cin >> R >> C;

    auto grid = vector<string>(R);
    for (auto& row : grid) cin >> row;

    for (auto& row : grid)
    {
        for (auto c = 0; c+1 < C; c++)
            if (row[c+1] == '?') row[c+1] = row[c];
        for (auto c = C-1; c-1 >= 0; c--)
            if (row[c-1] == '?') row[c-1] = row[c];
    }

    for (auto r = 0; r+1 < R; r++)
        if (grid[r+1][0] == '?') grid[r+1] = grid[r];
    for (auto r = R-1; r-1 >= 0; r--)
        if (grid[r-1][0] == '?') grid[r-1] = grid[r];

    for (const auto& row : grid)
        cout << row << endl;
}

int main()
{
    int T; cin >> T;
    for (auto t = 1; t <= T; t++)
    {
        cout << "Case #" << t << ": " << endl;
        solve_case();
    }
}
