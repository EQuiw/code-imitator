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

vvpi all;
vpi hor;
map<vi, double> mm;
priority_queue<pair<double, vi>> pq; // min-time, <idx, horse#, rem-dis>

double dij(int s, int t) {
  double re = 1e18;
  while (!pq.empty())
    pq.pop();
  mm.clear();
  vi tmp;
  tmp.push_back(s);
  tmp.push_back(-1);
  tmp.push_back(hor[s].first);
  pq.push(make_pair(0.0, tmp));
  mm[tmp] = 0.0;
  while (!pq.empty()) {
    pair<double, vi> now = pq.top();
    pq.pop();
    double nowtime = now.first;
    if (nowtime > mm[now.second])
      continue;
    int idx = (now.second)[0];
    if (idx == t)
      re = min(re, nowtime);
    int horse = (now.second)[1];
    int rem = (now.second)[2];
    int tsz = all[idx].size();
    // cout << idx << " " << horse << " "  << rem << " " << nowtime << endl;
    for (int i = (0); i < (tsz); i++) {
      int nxtidx = all[idx][i].first;
      int dis = all[idx][i].second;
      // Still the current house
      if (horse != -1 && rem >= dis) {
        double nxttime = nowtime + (double)dis / hor[horse].second;
        tmp.clear();
        tmp.push_back(nxtidx);
        tmp.push_back(horse);
        tmp.push_back(rem - dis);
        if (mm.find(tmp) == mm.end() || mm[tmp] > nxttime) {
          mm[tmp] = nxttime;
          pq.push(make_pair(nxttime, tmp));
        }
      }
      double nxttime = nowtime + (double)dis / hor[idx].second;
      tmp.clear();
      tmp.push_back(nxtidx);
      tmp.push_back(idx);
      tmp.push_back(hor[idx].first - dis);
      if (mm.find(tmp) == mm.end() || mm[tmp] > nxttime) {
        mm[tmp] = nxttime;
        pq.push(make_pair(nxttime, tmp));
      }
    }
  }
  return re;
}
int main() {
  int T;
  cin >> T;
  for (int test = (1); test < (T + 1); test++) {
    int n, q;
    cin >> n >> q;
    all.clear();
    hor.clear();
    all.assign(n, vpi(0, pi(0, 0)));
    for (int i = (0); i < (n); i++) {
      int e, s;
      cin >> e >> s;
      hor.push_back(make_pair(e, s));
    }
    for (int i = (0); i < (n); i++) {
      for (int j = (0); j < (n); j++) {
        int tmp;
        cin >> tmp;
        if (tmp != -1) {
          all[i].push_back(make_pair(j, tmp));
        }
      }
    }
    printf("Case #%d:", test);
    for (int i = (0); i < (q); i++) {
      int s, t;
      cin >> s >> t;
      s--;
      t--;
      double re = dij(s, t);
      printf(" %.7f", re);
    }
    printf("\n");
  }
  return 0;
}
