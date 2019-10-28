/*
 * Author: Vladislav Belov
 */
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

void solution();

int main() {
  ios::sync_with_stdio(false);
#ifdef HOME
  freopen("A.in", "rt", stdin);
  freopen("A.out", "wt", stdout);
  clock_t start = clock();
#endif
  solution();
#ifdef HOME
  cerr << "Total time: " << fixed << setprecision(3)
       << double(clock() - start) / double(CLOCKS_PER_SEC) << endl;
#endif
  return EXIT_SUCCESS;
}

typedef long long ll;
#define int ll

#define N 32
int n, m;
char a[N][N], b[N][N];
struct node {
  int x0, y0, x1, y1;
  node() : x0(N), y0(N), x1(-1), y1(-1) {}
  void apply(char ch) {
    for (int x = x0; x <= x1; ++x)
      for (int y = y0; y <= y1; ++y)
        b[x][y] = ch;
  }
} c[256];

void solve() {
  for (int i = 0; i < 256; ++i)
    c[i] = node();
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      b[i][j] = '?';
      int t = a[i][j];
      c[t].x0 = min(c[t].x0, i);
      c[t].y0 = min(c[t].y0, j);
      c[t].x1 = max(c[t].x1, i);
      c[t].y1 = max(c[t].y1, j);
    }
  for (int i = 0; i < 256; ++i) {
    if (c[i].x1 == -1)
      continue;
    c[i].apply(i);
  }
  for (int i = 0; i < 256; ++i) {
    if (c[i].x1 == -1)
      continue;
    for (;;) {
      /*
      for (int x = 0; x < n; ++x, cerr << endl)
          for (int y = 0; y < m; ++y)
              cerr << b[x][y];
      cerr << endl;
      */
      bool fnd = false;
      if (c[i].y0 > 0) {
        bool all = true;
        for (int x = c[i].x0; x <= c[i].x1; ++x)
          if (b[x][c[i].y0 - 1] != '?')
            all = false;
        if (all) {
          --c[i].y0;
          c[i].apply(i);
          fnd = true;
        }
      }
      if (c[i].x0 > 0) {
        bool all = true;
        for (int y = c[i].y0; y <= c[i].y1; ++y)
          if (b[c[i].x0 - 1][y] != '?')
            all = false;
        if (all) {
          --c[i].x0;
          c[i].apply(i);
          fnd = true;
        }
      }
      if (c[i].y1 < m - 1) {
        bool all = true;
        for (int x = c[i].x0; x <= c[i].x1; ++x)
          if (b[x][c[i].y1 + 1] != '?')
            all = false;
        if (all) {
          ++c[i].y1;
          c[i].apply(i);
          fnd = true;
        }
      }
      if (c[i].x1 < n - 1) {
        bool all = true;
        for (int y = c[i].y0; y <= c[i].y1; ++y)
          if (b[c[i].x1 + 1][y] != '?')
            all = false;
        if (all) {
          ++c[i].x1;
          c[i].apply(i);
          fnd = true;
        }
      }
      if (!fnd)
        break;
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j)
      cout << (char)b[i][j];
    cout << '\n';
  }
}

void solution() {
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    cerr << t + 1 << endl;
    cout << "Case #" << t + 1 << ":\n";
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        cin >> a[i][j];
    solve();
  }
}
