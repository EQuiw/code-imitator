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

int n, r, o, y, g, b, v;

string solve(int r, int y, int b) {
  int a[3] = {r, y, b};
  string t = "RYB";

  for (int i = 0; i < 3; ++i) {
    for (int j = i + 1; j < 3; ++j) {
      if (a[j] > a[i]) {
        swap(a[j], a[i]);
        swap(t[j], t[i]);
      }
    }
  }

  string res(n, ' ');
  for (int i = 0; i < n; i += 2) {
    for (int j = 0; j < 3; ++j) {
      if (a[j] > 0) {
        res[i] = t[j];
        --a[j];
        break;
      }
    }
  }
  for (int i = 1; i < n; i += 2) {
    for (int j = 0; j < 3; ++j) {
      if (a[j] > 0) {
        res[i] = t[j];
        --a[j];
        break;
      }
    }
  }

  bool ok = true;
  for (int i = 1; i < n; ++i) {
    if (res[i] == res[i - 1] || (n > 1 && res[0] == res[n - 1])) {
      ok = false;
    }
  }

  if (!ok) {
    cerr << "BAD" << endl;
  }

  return res;
}

void solve(int test) {
  cin >> n >> r >> o >> y >> g >> b >> v;
  if (2 * r > n || 2 * y > n || 2 * b > n) {
    printf("Case #%d: IMPOSSIBLE\n", test);
    return;
  }
  if (r + y + b != n) {
    printf("Case #%d: IMPOSSIBLE\n", test);
    return;
  }

  printf("Case #%d: %s\n", test, solve(r, y, b).c_str());
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
