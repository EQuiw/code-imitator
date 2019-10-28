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

int main()
{
	ios::sync_with_stdio(false);

	int T;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		string s;
		cin >> s;
		int K;
		cin >> K;

		int nbFlips = 0;
		for (int p = 0; p < s.size() - K + 1; p++)
		{
			if (s[p] == '-')
			{
				transform(s.begin() + p, s.begin() + p + K, s.begin() + p,
					[](char c)
				{
					return (c == '+' ? '-' : '+');
				});
				nbFlips++;
			}
		}

		if (any_of(s.begin(), s.end(), [](char c) { return (c == '-'); }))
			nbFlips = -1;

		cout << "Case #" << t + 1 << ": ";
		if (nbFlips >= 0)
			cout << nbFlips << endl;
		else
			cout << "IMPOSSIBLE" << endl;
	}

	return 0;
}
