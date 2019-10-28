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

ull hob(ull n)
{
	if (!n)
		return 0;
	ull ret = 1;
	while (n >>= 1)
		ret <<= 1;
	return ret;
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
		ull n, k;
		cin >> n >> k;
		ull h = hob(k);
		ull lo = k&(~h);
		h <<= 1;
		ull left = (n - lo) / h, right = (n - (lo+h/2)) / h;
		cout << "Case #" << t << ": " << left << " " << right << endl;
	}
	return 0;
}