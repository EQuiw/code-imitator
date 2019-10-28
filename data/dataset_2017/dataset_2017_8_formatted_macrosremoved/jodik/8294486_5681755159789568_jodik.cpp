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
    for (int i = 0; i < (n); i++) {
      cin >> e >> s;
      horses[i] = make_pair(e, s);
    }

    for (int i = 0; i < (n); i++) {
      for (int j = 0; j < (n); j++) {
        cin >> e;
        dist[i][j] = e;
      }
    }

    for (int i = 0; i < (q); i++) {
      cin >> u >> v;

      // rychlost, zostatok_drahy, ubehnuty cas
      vector<vector<long long>> cur_h;
      vector<ld> cur_h_cas;
      vector<long long> kon(2);
      kon[0] = horses[0].second;
      kon[1] = horses[0].first;
      cur_h.push_back(kon);
      cur_h_cas.push_back(0);
      // cout<<kon[0]<<" "<<kon[1]<<" "<<kon[2]<<" "<<endl;
      ld cas_novy_kon = 1000000000000000;
      for (int j = (1); j <= (n - 1); j++) {
        int draha = dist[j - 1][j];
        vector<bool> to_keep(cur_h.size(), true);
        cas_novy_kon = 1000000000000000;
        for (int k = 0; k < (cur_h.size()); k++) {
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
