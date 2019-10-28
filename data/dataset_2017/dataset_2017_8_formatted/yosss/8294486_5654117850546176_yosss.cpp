#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mp make_pair
#define pb push_back
#define fst first
#define snd second
const ll MODP = 1000000007;

ll n, r, o, y, g, b, v;
void solve(void) {
  cin >> n >> r >> o >> y >> g >> b >> v;
  if (g == 0 && v == 0 && o == 0) {
    vector<pair<int, char>> p;
    p.pb(mp(r, 'R'));
    p.pb(mp(b, 'B'));
    p.pb(mp(y, 'Y'));
    sort(p.begin(), p.end());
    if (p[0].fst + p[1].fst < p[2].fst) {
      cout << "IMPOSSIBLE" << endl;
      return;
    }
    string ret = "";
    int m1 = p[1].fst;
    char c1 = p[1].snd;
    int m0 = p[0].fst;
    char c0 = p[0].snd;
    for (int i = 0; i < p[2].fst; i++) {
      ret += p[2].snd;
      if (i + 1 == p[2].fst) {
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