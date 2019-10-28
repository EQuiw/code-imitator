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
#define endl "\n"
#define PI 3.1415926535897932384626433
#define OO (1L<<31)-1
#define eps 1e-9
#define mp(a, b)   make_pair((a), (b))
#define min(a, b)  ((a) < (b) ? (a) :  (b))
#define max(a, b)  ((a) > (b) ? (a) :  (b))
#define abs(a)     ((a) > 0   ? (a) : -(a))
#define sgn(a)     ((a) > eps ? 1 : ((a) < -eps ? -1 : 0))
#define cl1(x)     ((x)&((x)-1)) // clear lowest 1 bit
#define cl0(x)     ((x)|((x)+1)) // clear lowest 0 bit
#define ct1(x)     ((x)&((x)+1)) // clear all trailing 1 bits
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define MOD 1000000007
#define MAX_N 200000
using namespace std;

ull num[20][10];

void precompute()
{
	for (int i = 1; i <= 9; i++)
		num[1][i] = i;
	for (int i = 2; i <= 19; i++)
	{
		for (int j = 1; j <= 9; j++)
		{
			num[i][j] = num[i - 1][j] * 10 + j;
		}
	}
}

int digitCnt(ll n)
{
	if (n == 0)
		return 1;
	int ans = 0;
	while (n > 0)
	{
		ans++;
		n /= 10;
	}
	return ans;
}

ull solve(ull n)
{
	if (n <= 9)
		return n;
	int cnt = digitCnt(n);
	ull ans = 0;
	if (n < num[cnt][1])
		return num[cnt - 1][9];
	ull p = 1;
	for (int i = 0; i < cnt-1; i++)
		p *= 10;
	for (int i = 9; i >= 1; i--)
	{
		if (num[cnt][i] <= n)
		{
			ll x = num[cnt][i] / p;
			ll nn = n - x*p;
			if (nn > p)
				nn = num[cnt - 1][9];
			ll y = solve(nn);
			return x*p + y;
		}
	}
	return ans;
}

int main()
{
	FAST_IO
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	precompute();
	TESTS(t)
	{
		ull n;
		cin >> n;
		cout << "Case #" << t << ": " << solve(n) << endl;
	}
	return 0;
}