#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#pragma comment(linker, "/STACK:256000000")

using namespace std;

void readData() {}

const int maxN = 60;
const int maxL = 2000000;
int n, p;
int a[maxN];
int b[maxN][maxN];

int d[maxN][maxN];
int q[maxL];

pair<int, int> c[maxN][maxN];
bool used[maxN][maxN];

pair<int, int> getPackages(int value, int t) {
  int r = (value * 10) / (9 * t);
  int l = (value * 10 + 11 * t - 1) / (11 * t);

  return make_pair(l, r);
}

void solve(int test) {
  cin >> n >> p;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  for (int i = 0; i < maxL; ++i) {
    q[i] = 0;
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < p; ++j) {
      cin >> b[i][j];
      c[i][j] = getPackages(b[i][j], a[i]);
      for (int k = c[i][j].first; k <= c[i][j].second; ++k) {
        q[k] = true;
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < p; ++j) {
      used[i][j] = false;
    }
  }

  int res = 0;
  for (int k = 0; k < maxL; ++k) {
    if (!q[k]) {
      continue;
    }
    while (true) {
      bool good = true;
      for (int i = 0; i < n; ++i) {
        bool have = false;
        for (int j = 0; j < p; ++j) {
          if (used[i][j]) {
            continue;
          }
          if (k >= c[i][j].first && k <= c[i][j].second) {
            have = true;
            break;
          }
        }
        if (!have) {
          good = false;
          break;
        }
      }
      if (!good) {
        break;
      }
      ++res;
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
          if (used[i][j]) {
            continue;
          }
          if (k >= c[i][j].first && k <= c[i][j].second) {
            used[i][j] = true;
            break;
          }
        }
      }
    }
  }

  printf("Case #%d: %d\n", test, res);
}

int main(int argc, char *argv[]) {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int left_bound, right_bound;

  /*freopen(argv[3], "w", stdout);
  sscanf(argv[1], "%d", &left_bound);
  sscanf(argv[2], "%d", &right_bound);*/

  int t;
  cin >> t;
  left_bound = 1, right_bound = t;
  for (int i = 1; i <= t; ++i) {
    if (i >= left_bound && i <= right_bound) {
      solve(i);
    } else {
      readData();
    }
    cerr << i << ": " << clock() << endl;
  }

  return 0;
}
