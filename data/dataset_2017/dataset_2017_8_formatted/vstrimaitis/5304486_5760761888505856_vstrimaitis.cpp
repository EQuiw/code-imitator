#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <assert.h>
#include <bitset>
#include <climits>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef std::pair<int, int> pii;
template <typename T>
using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template <typename T>
using max_heap = std::priority_queue<T, std::vector<T>, std::less<T>>;

#define FAST_IO                                                                \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);
#define TESTS(t)                                                               \
  int NUMBER_OF_TESTS;                                                         \
  cin >> NUMBER_OF_TESTS;                                                      \
  for (int t = 1; t <= NUMBER_OF_TESTS; t++)
#define FOR(i, start, end) for (int i = (start); i < (end); i++)
#define ROF(i, start, end) for (int i = (start); i >= (end); i--)
#define all(x) (x).begin(), (x).end()
#define endl "\n"
#define PI 3.1415926535897932384626433
#define OO (1LL << 31) - 1
#define eps 1e-9
#define in(a, b) ((b).find(a) != (b).end())
#define mp(a, b) make_pair((a), (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define abs(a) ((a) > 0 ? (a) : -(a))
#define sgn(a) ((a) > eps ? 1 : ((a) < -eps ? -1 : 0))
#define cl1(x) ((x) & ((x)-1))   // clear lowest 1 bit
#define cl0(x) ((x) | ((x) + 1)) // clear lowest 0 bit
#define ct1(x) ((x) & ((x) + 1)) // clear all trailing 1 bits
#define pb push_back
#define MOD 1000000007
#define MAX_N 25
using namespace std;

string grid[MAX_N];
int rowCnt[MAX_N], colCnt[MAX_N];

int main() {
  FAST_IO
#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  TESTS(t) {
    int r, c;
    cin >> r >> c;
    FOR(i, 0, r) { cin >> grid[i]; }
    FOR(i, 0, r) {
      FOR(j, 0, c) {
        if (grid[i][j] != '?') {
          rowCnt[i]++;
          colCnt[j]++;
        }
      }
    }

    FOR(i, 0, r) {
      char curr = '?';
      FOR(j, 0, c) {
        if (grid[i][j] != '?') {
          curr = grid[i][j];
          ROF(jj, j - 1, 0) {
            if (grid[i][jj] != '?')
              break;
            grid[i][jj] = curr;
          }
        }
        if (curr != '?')
          grid[i][j] = curr;
      }
    }

    FOR(i, 1, r) {
      if (grid[i][0] == '?') {
        grid[i] = grid[i - 1];
      }
    }
    ROF(i, r - 2, 0) {
      if (grid[i][0] == '?')
        grid[i] = grid[i + 1];
    }

    cout << "Case #" << t << ":" << endl;
    FOR(i, 0, r)
    cout << grid[i] << endl;
  }
  return 0;
}