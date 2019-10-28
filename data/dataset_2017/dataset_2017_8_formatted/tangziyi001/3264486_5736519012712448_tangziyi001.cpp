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
#define REP(i, s, t) for (int i = (s); i < (t); i++)
#define FILL(x, v) memset(x, v, sizeof(x))
#define MAXN 1000
#define MOD 1000000007

int main() {
  int T;
  cin >> T;
  REP(t, 1, T + 1) {
    string line;
    int n;
    cin >> line >> n;
    int maxp = 0;
    int idx = 0;
    int sz = line.size();
    while (idx <= sz - n) {
      if (line[idx] == '-') {
        maxp++;
        REP(i, idx, idx + n) {
          if (line[i] == '-')
            line[i] = '+';
          else
            line[i] = '-';
        }
      }
      idx++;
    }
    int flag = 1;
    while (idx < sz) {
      if (line[idx] == '-') {
        flag = 0;
        break;
      }
      idx++;
    }
    if (flag) {
      printf("Case #%d: %d\n", t, maxp);
    } else {
      printf("Case #%d: IMPOSSIBLE\n", t);
    }
  }
  return 0;
}