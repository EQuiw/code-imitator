#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory.h>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> PII;
typedef long long LL;
const int INF = 0x3f3f3f3f;

const int N = 30;

char grid[N][N];

int main() {
  int test;
  scanf("%d", &test);
  for (int cas = 0; cas < test; cas++) {
    long long ans = 0;
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        scanf(" %c", &grid[i][j]);
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 1; j < m; j++) {
        if (grid[i][j] == '?' && grid[i][j - 1] != '?') {
          grid[i][j] = grid[i][j - 1];
        }
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = m - 2; j >= 0; j--) {
        if (grid[i][j] == '?' && grid[i][j + 1] != '?') {
          grid[i][j] = grid[i][j + 1];
        }
      }
    }

    for (int j = 0; j < m; j++) {
      for (int i = 1; i < n; i++) {
        if (grid[i][j] == '?' && grid[i - 1][j] != '?') {
          grid[i][j] = grid[i - 1][j];
        }
      }
    }
    for (int j = 0; j < m; j++) {
      for (int i = n - 2; i >= 0; i--) {
        if (grid[i][j] == '?' && grid[i + 1][j] != '?') {
          grid[i][j] = grid[i + 1][j];
        }
      }
    }
    printf("Case #%d:\n", cas + 1);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        printf("%c", grid[i][j]);
      }
      printf("\n");
    }
  }
}
