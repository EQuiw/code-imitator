#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <climits>
#include <set>
#include <bitset>
#include <math.h>
#include <queue>
#include <map>
#include <sstream>
#include <functional>
#include <assert.h>
#include <unordered_map>
#include <unordered_set>
#include <complex>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef std::pair<int, int> pii;
template <typename T> using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template <typename T> using max_heap = std::priority_queue<T, std::vector<T>, std::less<T>>;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define TESTS(t) int NUMBER_OF_TESTS; cin >> NUMBER_OF_TESTS; for(int t = 1; t <= NUMBER_OF_TESTS; t++)
#define FOR(i, start, end) for(int i = (start); i < (end); i++)
#define ROF(i, start, end) for(int i = (start); i >= (end); i--)
#define all(x) (x).begin(), (x).end()
#define endl "\n"
#define PI 3.1415926535897932384626433
#define OO (1LL<<31)-1
#define eps 1e-9
#define in(a,b)    ((b).find(a) != (b).end())
#define mp(a, b)   make_pair((a), (b))
#define min(a, b)  ((a) < (b) ? (a) :  (b))
#define max(a, b)  ((a) > (b) ? (a) :  (b))
#define abs(a)     ((a) > 0   ? (a) : -(a))
#define sgn(a)     ((a) > eps ? 1 : ((a) < -eps ? -1 : 0))
#define cl1(x)     ((x)&((x)-1)) // clear lowest 1 bit
#define cl0(x)     ((x)|((x)+1)) // clear lowest 0 bit
#define ct1(x)     ((x)&((x)+1)) // clear all trailing 1 bits
#define pb push_back
#define MOD 1000000007
#define MAX_N 100
using namespace std;

ll w[MAX_N][MAX_N];
ll e[MAX_N], s[MAX_N];
int n, q;
ld best[MAX_N][MAX_N];

ld solve(int u, int v)
{
	FOR(i, 0, n)
		FOR(j, 0, n)
			best[i][j] = OO;
	best[n - 1][n-1] = 0;
	ROF(i, n - 2, 0)
	{
		best[i][i] = 0;
		ll totalDist = 0;
		int prev = i;
		FOR(j, i + 1, n)
		{
			if (w[prev][j] < 0)
				continue;
			totalDist += w[prev][j];
			if (totalDist > e[i])
			{
				FOR(k, j, n)
				{
					best[i][k] = best[i][prev] + best[prev][k];
				}
				break;
			}
			best[i][j] = min(totalDist / (ld)s[i], best[i][prev] + w[prev][j]/(ld)s[prev]);
			prev = j;
		}
	}
	return best[0][n - 1];
}

int main()
{
	FAST_IO
#ifdef _DEBUG
#endif
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	TESTS(t)
	{
		cin >> n >> q;
		FOR(i, 0, n)
		{
			cin >> e[i] >> s[i];
		}
		FOR(i, 0, n)
		{
			FOR(j, 0, n)
			{
				int a;
				cin >> a;
				w[i][j] = a;
			}
		}
		cout << "Case #" << t << ": ";
		FOR(i, 0, q)
		{
			int u, v;
			cin >> u >> v;
			cout << fixed << setprecision(12) << solve(u, v) << " ";
		}
		cout << endl;
	}
	return 0;
}
