#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

typedef long long LL;
typedef long double LD;

int cond = 1;

int solve() {
  int r, c;
  cin >> r >> c;
  vector<string> res;
  for (int i = 0; i < r; ++i) {
    string row;
    cin >> row;
    bool empty = true;
    char first = '?';
    for (int j = 0; j < c; ++j) {
      if (row[j] != '?') {
        empty = false;
        first = row[j];
        break;
      }
    }
    if (!empty) {
      string s(c, '?');
      for (int j = 0; j < c; ++j) {
        if (row[j] == first || row[j] == '?') {
          s[j] = first;
        } else {
          first = row[j];
          s[j] = first;
        }
      }
      while (res.size() < i + 1) {
        res.push_back(s);
      }
    } else {
      if (res.size() > 0) {
        res.push_back(res[res.size() - 1]);
      }
    }
  }
  for (int i = 0; i < r; ++i) {
    cout << res[i] << endl;
  }
  return 0;
}

int main() {
  int t;
  cin >> t;
  for (int x = 1; x <= t; ++x) {
    cout << "Case #" << x << ": " << endl;
    solve(); // result
  }
  return 0;
}
