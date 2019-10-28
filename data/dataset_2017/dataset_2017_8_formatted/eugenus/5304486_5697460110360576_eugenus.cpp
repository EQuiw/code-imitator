#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

#define forn(i, n) for (int i = 0; i < (n); i++)
#define forsn(i, s, n) for (int i = (s); i < (n); i++)
#define all(v) ((v).begin, (v).end)
#define pb push_back
#define x first
#define y second
#define mp make_pair

using namespace std;

typedef pair<int, int> par;
typedef long long int tint;

int r[55];
int q[55][55];
par cand[55][55];

int main() {
  freopen("test.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int t;
  cin >> t;
  int n, p;

  forsn(caso, 1, t + 1) {
    cin >> n >> p;
    vector<int> l;
    forn(i, n) cin >> r[i];
    bool used[55][55];
    forn(i, n) forn(j, n) used[i][j] = false;
    forn(i, n) { forn(j, p) cin >> q[i][j]; }
    forn(i, n) {
      forn(j, p) {
        int a = (100 * q[i][j] + 110 * r[i] - 1) / (110 * r[i]);
        a = max(a, 1);
        int b = (100 * q[i][j]) / (90 * r[i]);
        if (a <= b)
          l.pb(a);
        par p;
        p.x = b - a;
        p.y = b;
        cand[i][j] = p;
      }
      sort(cand[i], cand[i] + p);
    }
    sort(l.begin(), l.end());
    int ans = 0;

    forn(m, l.size()) {
      bool ok = true;
      int k = l[m];
      int ac[55];
      forn(i, n) {
        bool oki = false;
        forn(j, p) {
          if (!used[i][j]) {
            int a = cand[i][j].y - cand[i][j].x;
            int b = cand[i][j].y;
            if (a <= k and k <= b) {
              // used[i][j] = true;
              ac[i] = j;
              oki = true;
              break;
            }
          }
        }
        if (!oki) {
          ok = false;
          break;
        }
      }

      if (ok) {
        // cout << k << endl;
        forn(i, n) used[i][ac[i]] = true;
        ans++;
      }
    }

    cout << "Case #" << caso << ": " << ans << endl;
  }

  return 0;
}