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
#define MAX_N 50
using namespace std;

int w[MAX_N+2][MAX_N][MAX_N+2][MAX_N];
int rW[MAX_N + 2][MAX_N][MAX_N + 2][MAX_N];
pii parent[MAX_N + 2][MAX_N];
int n, p;
int r[MAX_N];
int q[MAX_N+2][MAX_N];
pii interval[MAX_N+2][MAX_N];
bool visited[MAX_N + 2][MAX_N];

bool intersect(pii i1, pii i2)
{
	if (i1.second < i2.first || i1.first > i2.second)
		return false;
	return true;
}

bool bfs(pii s, pii t)
{
	FOR(i, 0, n + 2)
	{
		FOR(j, 0, p)
		{
			visited[i][j] = false;
		}
	}
	queue <pii> q;
	q.push(s);
	visited[s.first][s.second] = true;
	parent[s.first][s.second] = { -1, -1 };
	while (!q.empty())
	{
		pii u = q.front();
		q.pop();
		FOR(i, 0, n + 2)
		{
			FOR(j, 0, p)
			{
				if (!visited[i][j] && rW[u.first][u.second][i][j] > 0)
				{
					q.push({ i, j });
					parent[i][j] = u;
					visited[i][j] = true;
				}
			}
		}
	}
	return (visited[t.first][t.second] == true);
}

int ford(pii s, pii t)
{
	pii u, v;
	FOR(i, 0, n + 2)
	{
		FOR(j, 0, p)
		{
			FOR(ii, 0, n + 2)
			{
				FOR(jj, 0, p)
				{
					rW[i][j][ii][jj] = w[i][j][ii][jj];
				}
			}
		}
	}

	int max_flow = 0;
	while (bfs(s, t))
	{
		int path_flow = INT_MAX;
		for (v = t; v != s; v = parent[v.first][v.second])
		{
			u = parent[v.first][v.second];
			path_flow = min(path_flow, rW[u.first][u.second][v.first][v.second]);
		}

		for (v = t; v != s; v = parent[v.first][v.second])
		{
			u = parent[v.first][v.second];
			rW[u.first][u.second][v.first][v.second] -= path_flow;
			rW[v.first][v.second][u.first][u.second] += path_flow;
		}

		max_flow += path_flow;
	}

	return max_flow;
}

void reset()
{
	FOR(i, 0, n + 2)
	{
		FOR(j, 0, p)
		{
			FOR(ii, 0, n + 2)
			{
				FOR(jj, 0, p)
				{
					w[i][j][ii][jj] = 0;
					rW[i][j][ii][jj] = 0;
				}
			}
		}
	}

	FOR(i, 0, n + 2)
	{
		FOR(j, 0, p)
		{
			parent[i][j] = { -1, -1 };
		}
	}

}

bool isValid(pii interval)
{
	return interval.first <= interval.second;
}

int main()
{
	FAST_IO
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	TESTS(t)
	{
		cin >> n >> p;
		reset();
		FOR(i, 1, n+1)
		{
			cin >> r[i];
		}
		FOR(i, 1, n+1)
		{
			FOR(j, 0, p)
			{
				cin >> q[i][j];
				interval[i][j] = { (int)ceil(q[i][j] / (1.1*r[i])), (int)floor(q[i][j] / (0.9*r[i])) };
			}
		}
		FOR(j, 0, p)
		{
			if(isValid(interval[1][j]))
				w[0][0][1][j] = 1;
			if (isValid(interval[n][j]))
				w[n][j][n + 1][0] = 1;
		}
		FOR(i, 0, n)
		{
			FOR(j, 0, p)
			{
				FOR(k, 0, p)
				{
					if (intersect(interval[i][j], interval[i + 1][k]) && isValid(interval[i][j]) && isValid(interval[i+1][k]))
					{
						w[i][j][i + 1][k] = 1;
					}
				}
			}
		}
		cout << "Case #" << t << ": " << ford({ 0, 0 }, { n + 1, 0 }) << endl;
	}
	return 0;
}