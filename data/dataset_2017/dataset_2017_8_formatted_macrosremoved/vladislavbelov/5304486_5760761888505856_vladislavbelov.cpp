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

  solution();

  return EXIT_SUCCESS;
}

typedef long long ll;

ll n, m;
char a[32][32], b[32][32];
struct node {
  ll x0, y0, x1, y1;
  node() : x0(32), y0(32), x1(-1), y1(-1) {}
  void apply(char ch) {
    for (ll x = x0; x <= x1; ++x)
      for (ll y = y0; y <= y1; ++y)
        b[x][y] = ch;
  }
} c[256];

void solve() {
  for (ll i = 0; i < 256; ++i)
    c[i] = node();
  for (ll i = 0; i < n; ++i)
    for (ll j = 0; j < m; ++j) {
      b[i][j] = '?';
      ll t = a[i][j];
      c[t].x0 = min(c[t].x0, i);
      c[t].y0 = min(c[t].y0, j);
      c[t].x1 = max(c[t].x1, i);
      c[t].y1 = max(c[t].y1, j);
    }
  for (ll i = 0; i < 256; ++i) {
    if (c[i].x1 == -1)
      continue;
    c[i].apply(i);
  }
  for (ll i = 0; i < 256; ++i) {
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
        for (ll x = c[i].x0; x <= c[i].x1; ++x)
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
        for (ll y = c[i].y0; y <= c[i].y1; ++y)
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
        for (ll x = c[i].x0; x <= c[i].x1; ++x)
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
        for (ll y = c[i].y0; y <= c[i].y1; ++y)
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
  for (ll i = 0; i < n; ++i) {
    for (ll j = 0; j < m; ++j)
      cout << (char)b[i][j];
    cout << '\n';
  }
}

void solution() {
  ll T;
  cin >> T;
  for (ll t = 0; t < T; ++t) {
    cerr << t + 1 << endl;
    cout << "Case #" << t + 1 << ":\n";
    cin >> n >> m;
    for (ll i = 0; i < n; ++i)
      for (ll j = 0; j < m; ++j)
        cin >> a[i][j];
    solve();
  }
}
