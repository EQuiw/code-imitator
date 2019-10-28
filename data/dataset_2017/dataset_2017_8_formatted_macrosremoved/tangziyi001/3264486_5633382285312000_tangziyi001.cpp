/*
 *
 *	Created by Ziyi Tang
 *
 */

//#include <bits/stdc++.h>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pi;
typedef vector<pi> vpi;
typedef vector<vpi> vvpi;
const int INF = 0x3f3f3f;
const ll INFL = (ll)1E18;
const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int main() {
  int T;
  cin >> T;
  for (int t = (1); t < (T + 1); t++) {
    string line;
    cin >> line;
    int sz = line.size();
    int idx = -1;
    for (int i = sz - 1; i > 0; i--) {
      char now = line[i];
      char pre = line[i - 1];
      int num = (int)now - (int)('0');
      int prenum = (int)pre - (int)('0');
      if (num < prenum) {
        idx = i;
        prenum = prenum - 1;
        if (prenum == -1)
          prenum = 9;
      }
      line[i - 1] = prenum + (int)('0');
      // cout << line << endl;
    }
    if (idx != -1) {
      for (int i = (idx); i < (sz); i++) {
        line[i] = '9';
      }
    }
    ll re = stoll(line);
    printf("Case #%d: %lld\n", t, re);
  }
  return 0;
}
