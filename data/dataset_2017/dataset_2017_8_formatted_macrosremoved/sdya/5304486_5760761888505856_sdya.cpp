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

const int maxN = 50;
string s[maxN];
int n, m;

void solve(int test) {
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    cin >> s[i];
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 1; j < m; ++j) {
      if (s[i][j] == '?') {
        s[i][j] = s[i][j - 1];
      }
    }
    for (int j = m - 2; j >= 0; --j) {
      if (s[i][j] == '?') {
        s[i][j] = s[i][j + 1];
      }
    }
  }

  for (int j = 0; j < m; ++j) {
    for (int i = 1; i < n; ++i) {
      if (s[i][j] == '?') {
        s[i][j] = s[i - 1][j];
      }
    }
    for (int i = n - 2; i >= 0; --i) {
      if (s[i][j] == '?') {
        s[i][j] = s[i + 1][j];
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (s[i][j] == '?') {
        cerr << "BAD" << endl;
      }
    }
  }

  printf("Case #%d:\n", test);
  for (int i = 0; i < n; ++i) {
    printf("%s\n", s[i].c_str());
  }
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
