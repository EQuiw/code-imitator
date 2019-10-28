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
const ll INFL = (ll)1E18 + 10;
const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int main() {
  int T;
  cin >> T;
  for (int t = (1); t < (T + 1); t++) {
    ll n, k;
    cin >> n >> k;
    priority_queue<ll> pq;
    pq.push(n);
    ll minp = n;
    ll maxp = n;
    while (k--) {
      ll now = pq.top();
      pq.pop();
      if (now & 1) {
        pq.push((now - 1) / 2);
        pq.push((now - 1) / 2);
        minp = min(minp, (now - 1) / 2);
        maxp = min(maxp, (now - 1) / 2);
      } else {
        pq.push((now - 1) / 2);
        pq.push(now / 2);
        minp = min(minp, (now - 1) / 2);
        maxp = min(maxp, now / 2);
      }
    }
    printf("Case #%d: %lld %lld\n", t, maxp, minp);
  }
  return 0;
}
