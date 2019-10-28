#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <complex>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <stdarg.h>
#include <string>
#include <vector>

// M_PI SI TREBA ODLOZIT

using namespace std;

typedef long double ld;

char opposite(char c) {
  if (c == '-')
    return '+';
  else
    return '-';
}

vector<long long> rece;
vector<vector<long long>> pack;
vector<vector<pair<long long, long long>>> ranges;
vector<int> indicies;
long long t, n, p;

bool porovnaj(const pair<long long, long long> &a,
              const pair<long long, long long> &b) {
  return a.first < b.first || (a.first == b.first && a.second < b.second);
}

int main() {
  // string m;
  cin >> t;

  for (long long tt = 0; tt < t; tt++) {
    cin >> n >> p;
    rece.clear();
    rece.resize(n);
    pack.clear();
    pack.resize(n, vector<long long>(p));
    indicies.clear();
    indicies.resize(n, 0);
    ranges.clear();
    ranges.resize(n, vector<pair<long long, long long>>(p));

    for (int i = 0; i < (n); i++) {
      cin >> rece[i];
    }

    for (int i = 0; i < (n); i++) {
      for (int j = 0; j < (p); j++) {
        cin >> pack[i][j];
      }
    }

    for (int i = 0; i < (n); i++) {
      rece[i] *= 11 * 9;
      for (int j = 0; j < (p); j++) {
        long long mi = (pack[i][j] * 10) * 9;
        long long ma = (pack[i][j] * 10) * 11;
        // cout<<mi<<" "<<ma<<" "<<rece[i]<<endl;
        long long mi2 = mi / rece[i];
        long long ma2 = ma / rece[i];
        if (mi % rece[i])
          mi2++;
        ranges[i][j] = make_pair(mi2, ma2);
        //   cout<<"ranges "<<i<<" "<< j<<": "<<mi2<<", "<<ma2<<endl;
      }
      // cout<<endl;
    }

    for (int i = 0; i < (n); i++) {
      sort(ranges[i].begin(), ranges[i].end(), porovnaj);
    }

    int res = 0;

    bool con = true;
    while (con) {
      long long max_mi = 0;
      long long min_ma = 100000000ll;
      for (int i = 0; i < (n); i++) {
        int in = indicies[i];
        max_mi = max(ranges[i][in].first, max_mi);
        min_ma = min(ranges[i][in].second, min_ma);
      }
      if (max_mi <= min_ma) {
        res++;
        for (int i = 0; i < (n); i++) {
          indicies[i]++;
          // cout<<indicies[i]<<" "<<p<<endl;
          if (indicies[i] >= p) {
            con = false;
            break;
          }
        }
      } else {
        for (int i = 0; i < (n); i++) {
          int in = indicies[i];
          if (ranges[i][in].second < max_mi) {
            indicies[i]++;
            if (indicies[i] >= p) {
              con = false;
              break;
            }
          }
        }
      }
    }

    cout << "Case #" << (tt + 1) << ": " << res << endl;
  }
}
