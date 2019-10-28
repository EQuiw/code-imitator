#include <bits/stdc++.h>
using namespace std;

const long long MODP = 1000000007;

long long n, r, o, y, g, b, v;
void solve(void) {
  cin >> n >> r >> o >> y >> g >> b >> v;
  if (g == 0 && v == 0 && o == 0) {
    vector<pair<int, char>> p;
    p.push_back(make_pair(r, 'R'));
    p.push_back(make_pair(b, 'B'));
    p.push_back(make_pair(y, 'Y'));
    sort(p.begin(), p.end());
    if (p[0].first + p[1].first < p[2].first) {
      cout << "IMPOSSIBLE" << endl;
      return;
    }
    string ret = "";
    int m1 = p[1].first;
    char c1 = p[1].second;
    int m0 = p[0].first;
    char c0 = p[0].second;
    for (int i = 0; i < p[2].first; i++) {
      ret += p[2].second;
      if (i + 1 == p[2].first) {
        if (m0 < m1) {
          for (int j = 0; j < m0; j++) {
            ret += c1;
            ret += c0;
          }
          ret += c1;
        } else if (m0 > m1) {
          for (int j = 0; j < m1; j++) {
            ret += c0;
            ret += c1;
          }
          ret += c0;
        } else {
          for (int j = 0; j < m1; j++) {
            ret += c0;
            ret += c1;
          }
        }
      } else {
        if (m0 < m1) {
          ret += c1;
          m1--;
        } else {
          ret += c0;
          m0--;
        }
      }
    }
    cout << ret << endl;
  }

  return;
}

int main(void) {
  int T;
  cin >> T;
  for (int tcnt = 1; tcnt <= T; tcnt++) {
    cout << "Case #" << tcnt << ": ";
    solve();
  }
  return 0;
}
