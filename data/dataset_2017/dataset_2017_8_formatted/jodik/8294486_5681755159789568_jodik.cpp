#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <complex>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <stdarg.h>
#include <string>
#include <tuple>
#include <vector>

#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define FORD(i, a, b) for (int i = (a); i >= (b); i--)
#define REP(i, b) for (int i = 0; i < (b); i++)
#define ll long long
#define nl printf("\n")

// M_PI SI TREBA ODLOZIT

using namespace std;

typedef long double ld;

int main() {
  // string m;
  int t;
  int q, n;
  cin >> t;
  for (int tt = 0; tt < t; tt++) {
    cout << "Case #" << (tt + 1) << ":";
    cin >> n >> q;
    vector<pair<int, int>> horses(n);
    vector<vector<int>> dist(n, vector<int>(n));
    int e, s, u, v;
    REP(i, n) {
      cin >> e >> s;
      horses[i] = make_pair(e, s);
    }

    REP(i, n) {
      REP(j, n) {
        cin >> e;
        dist[i][j] = e;
      }
    }

    REP(i, q) {
      cin >> u >> v;

      // rychlost, zostatok_drahy, ubehnuty cas
      vector<vector<ll>> cur_h;
      vector<ld> cur_h_cas;
      vector<ll> kon(2);
      kon[0] = horses[0].second;
      kon[1] = horses[0].first;
      cur_h.push_back(kon);
      cur_h_cas.push_back(0);
      // cout<<kon[0]<<" "<<kon[1]<<" "<<kon[2]<<" "<<endl;
      ld cas_novy_kon = 1000000000000000;
      FOR(j, 1, n - 1) {
        int draha = dist[j - 1][j];
        vector<bool> to_keep(cur_h.size(), true);
        cas_novy_kon = 1000000000000000;
        REP(k, cur_h.size()) {
          cur_h[k][1] -= draha;
          cur_h_cas[k] += draha / ((ld)cur_h[k][0]);
          if (cur_h[k][1] < 0) {
            to_keep[k] = false;
          } else if (cas_novy_kon > cur_h_cas[k]) {
            cas_novy_kon = cur_h_cas[k];
          }
        }
        kon[0] = horses[j].second;
        kon[1] = horses[j].first;
        cur_h.push_back(kon);
        cur_h_cas.push_back(cas_novy_kon);
        // cout<<kon[0]<<" "<<kon[1]<<" "<<kon[2]<<" "<<endl;
      }
      cout << std::fixed << std::setprecision(12) << " " << cas_novy_kon;
    }
    cout << endl;
  }
}