#include <algorithm>
#include <array>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <deque>
#include <forward_list>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <vector>

using namespace std;

vector<string> solve(int R, int C, vector<string> grid)
{
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (grid[i][j] != '?')
			{
				char fillChar = grid[i][j];
				for (int j2 = j; j2 >= 0; j2--)
				{
					if (grid[i][j2] != '?' && grid[i][j2] != fillChar)
						break;
					grid[i][j2] = fillChar;
				}
				for (int j2 = j; j2 < C; j2++)
				{
					if (grid[i][j2] != '?' && grid[i][j2] != fillChar)
						break;
					grid[i][j2] = fillChar;
				}
			}
		}
	}
	for (int i = 0; i < R; i++)
	{
		if (grid[i][0] == '?')
		{
			if (i > 0)
				grid[i] = grid[i - 1];
		}
	}
	for (int i = R - 1; i >= 0; i--)
	{
		if (grid[i][0] == '?')
		{
			if (i < R - 1)
				grid[i] = grid[i + 1];
		}
	}
	return grid;
}

int main()
{
	ios::sync_with_stdio(false);

	int T;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		int R, C;
		cin >> R >> C;

		vector<string> initialGrid(R);
		for (int i = 0; i < R; i++)
			cin >> initialGrid[i];

		vector<string> finalGrid = solve(R, C, initialGrid);

		cout << "Case #" << t + 1 << ':' << endl;
		for (const string& r : finalGrid)
			cout << r << endl;
	}

	return 0;
}
