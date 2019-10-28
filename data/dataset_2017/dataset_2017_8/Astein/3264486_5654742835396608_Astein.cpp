#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <queue>
#include <map>

using namespace std;

int main()
{
	freopen("C-small-1-attempt0.in", "r", stdin);
	freopen("C-small-1.out", "w", stdout);

	int T;
	cin >> T;
	
	for (int cn = 1; cn <= T; ++cn)
	{
		long long N, K;
		cin >> N >> K;

		map<long long, long long> cnt_map;
		priority_queue<long long> Q;
		Q.push(N);
		cnt_map[N] = 1;

		while (K > 0)
		{
			long long maxv = Q.top(); Q.pop();

			if (K <= cnt_map[maxv])
			{
				cout << "Case #" << cn << ": " << maxv / 2 << " " << (maxv - 1) / 2 << endl;
				break;
			}

			K -= cnt_map[maxv];

			if (cnt_map.count(maxv / 2) == 0)
			{
				Q.push(maxv / 2);
			}
			cnt_map[maxv / 2] += cnt_map[maxv];

			if (cnt_map.count((maxv - 1) / 2) == 0)
			{
				Q.push((maxv - 1) / 2);
			}
			cnt_map[(maxv - 1) / 2] += cnt_map[maxv];
		}
	}
}