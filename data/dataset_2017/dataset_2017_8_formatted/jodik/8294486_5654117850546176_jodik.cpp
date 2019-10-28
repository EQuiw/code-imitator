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
#include <vector>

#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define FORD(i, a, b) for (int i = (a); i >= (b); i--)
#define REP(i, b) for (int i = 0; i < (b); i++)
#define ll long long
#define nl printf("\n")

// M_PI SI TREBA ODLOZIT

using namespace std;

typedef long double ld;

string daj_pismenko(int maxi) {
  if (maxi == 0) {
    return "R";
  } else if (maxi == 2) {
    return "Y";
  } else {
    return "B";
  }
}

pair<bool, string> skus_opravit(string co) {
  int i = co.size() - 2;
  bool bolo = false;
  while (i > 0) {
    if (co[i] != co[i + 1]) {
      bolo = true;
      break;
    }
    char c = co[i];
    co[i] = co[i - 1];
    co[i - 1] = c;
    i -= 2;
  }

  return make_pair(bolo, co);
}

int main() {
  // string m;
  int t;
  ll d, n;
  cin >> t;
  vector<int> kone(6);
  for (int tt = 0; tt < t; tt++) {
    cout << "Case #" << (tt + 1) << ": ";
    cin >> n;
    REP(i, 6) { cin >> kone[i]; }
    string vysl = "";
    int posl = -1;
    while (n--) {
      vector<pair<int, int>> moznosti(6);
      REP(i, 6) {
        if (i != posl && kone[i] > 0)
          moznosti.push_back(make_pair(kone[i], i));
      }
      int maxx = -4;
      int maxi = -4;
      REP(i, moznosti.size()) {
        if (moznosti[i].first > maxx) {
          maxx = moznosti[i].first;
          maxi = moznosti[i].second;
        }
      }
      if (maxx == -4) {
        vysl += daj_pismenko(posl);
        kone[posl]--;
        auto vy = skus_opravit(vysl);
        // cout<<"tu"<<endl
        if (vy.first == false) {
          vysl = "IMPOSSIBLE";
          break;
        } else {
          vysl = vy.second;
        }
      } else {

        kone[maxi]--;
        posl = maxi;
        // cout<<maxi<<endl;
        vysl += daj_pismenko(maxi);
      }
    }
    // cout<<vysl<<endl;
    if (vysl[0] == vysl[vysl.size() - 1]) {
      string vyslc = vysl;
      REP(i, vysl.size() - 1) { vyslc[i] = vysl[i + 1]; }
      vyslc[vysl.size() - 1] = vysl[0];

      auto vy = skus_opravit(vyslc);
      // cout<<"tu"<<endl;
      if (vy.first == false ||
          vy.second[0] == vy.second[vy.second.size() - 1]) {
        vysl = "IMPOSSIBLE";
      } else {
        vysl = vy.second;
      }
    }
    cout << vysl << endl;
  }
}