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
    vpi all;
    int d, n;
    cin >> d >> n;
    for (int i = (0); i < (n); i++) {
      int k, s;
      cin >> k >> s;
      all.push_back(make_pair(k, s));
    }
    double tt = 0.0;
    for (int i = (0); i < (n); i++) {
      double ttt = ((double)d - all[i].first) / all[i].second;
      tt = max(tt, ttt);
    }
    printf("Case #%d: %.7f\n", t, (double)d / tt);
  }
  return 0;
}
