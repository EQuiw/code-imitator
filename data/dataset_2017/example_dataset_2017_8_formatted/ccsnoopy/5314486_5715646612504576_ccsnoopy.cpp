#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long LL;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

#ifdef DEBUG
#define cek(x) cout << x
#else
#define cek(x)                                                                 \
  if (false) {                                                                 \
  }
#endif // DEBUG

#define fi first
#define se second
#define INF 1000000000
#define INFLL 1000000000000000000LL
#define EPS 1e-9
#define PI acos(-1.0)
#define pb push_back
#define TC() while (tc--)
#define FOR(i, n) for (int i = 0; i < n; i++)
#define FORN(i, n) for (int i = 0; i <= n; i++)
#define REP(i, a, b) for (int i = a; i < b; i++)
#define REPN(i, a, b) for (int i = a; i <= b; i++)
#define reset(a, b) memset(a, b, sizeof(a))
#define ALL(v) v.begin(), v.end()
#define SORT(v) sort(ALL(v))
#define SORTA(v, n) sort(v, v + n)
#define SZ(v) (int)v.size()
#define sc(x) scanf("%d", &x)

void open() {
  freopen("D:/OneDrive/Code/GCJ/C-small-attempt3.in", "r", stdin);
  freopen("D:/OneDrive/Code/GCJ/out2.txt", "w", stdout);
}

int main(void) {
  open();
  int tc;
  sc(tc);
  char str[10][70];

  for (int ctr = 1; ctr <= tc; ctr++) {
    int r, c;
    map<ii, int> mp;
    int ct = 0;
    sc(r);
    sc(c);
    FOR(i, r) { scanf("%s", str[i]); }
    bool bs[2][120];
    reset(bs, true);
    bool possible = true;
    set<ii> s;
    vii v;
    FOR(i, r) {
      FOR(j, c) {
        if (str[i][j] == '|' || str[i][j] == '-') {
          mp[ii(i, j)] = ct++;
          int tmpi, tmpj;
          tmpi = i;
          tmpj = j;
          bool valid = true;
          while (true) {
            tmpi--;
            if (tmpi >= 0) {
              if (str[tmpi][j] == '#')
                break;
              if (str[tmpi][j] == '|' || str[tmpi][j] == '-') {
                valid = false;
                break;
              }
            } else
              break;
          }
          tmpi = i;
          while (true) {
            tmpi++;
            if (tmpi < r) {
              if (str[tmpi][j] == '#')
                break;
              if (str[tmpi][j] == '|' || str[tmpi][j] == '-') {
                valid = false;
                break;
              }
            } else
              break;
          }

          if (!valid) {
            bs[0][mp[ii(i, j)]] = false;
          }

          valid = true;

          while (true) {
            tmpj--;
            if (tmpj >= 0) {
              if (str[i][tmpj] == '#')
                break;
              if (str[i][tmpj] == '|' || str[i][tmpj] == '-') {
                valid = false;
                break;
              }
            } else
              break;
          }
          tmpj = j;
          while (true) {
            tmpj++;
            if (tmpj < c) {
              if (str[i][tmpj] == '#')
                break;
              if (str[i][tmpj] == '|' || str[i][tmpj] == '-') {
                valid = false;
                break;
              }
            } else
              break;
          }

          if (!valid) {
            bs[1][mp[ii(i, j)]] = false;
          }

          if (!bs[0][mp[ii(i, j)]] && !bs[1][mp[ii(i, j)]])
            possible = false;
        }
      }
    }

    FOR(i, r) {
      FOR(j, c) {
        if (str[i][j] == '.') {
          v.pb(ii(i, j));
          bool found = false;
          for (int k = i + 1; k < r; k++) {
            if (str[k][j] == '#')
              break;
            if (str[k][j] == '-' || str[k][j] == '|') {
              if (bs[0][mp[ii(k, j)]]) {

                if (bs[1][mp[ii(k, j)]])
                  s.insert(ii(k, j));
                found = true;
              }
            }
          }
          for (int k = i - 1; k >= 0; k--) {
            if (str[k][j] == '#')
              break;
            if (str[k][j] == '-' || str[k][j] == '|') {
              if (bs[0][mp[ii(k, j)]]) {
                found = true;
                if (bs[1][mp[ii(k, j)]])
                  s.insert(ii(k, j));
              }
            }
          }

          for (int k = j + 1; k < c; k++) {
            if (str[i][k] == '#')
              break;
            if (str[i][k] == '-' || str[i][k] == '|') {
              if (bs[1][mp[ii(i, k)]]) {
                found = true;
                if (bs[0][mp[ii(i, k)]])
                  s.insert(ii(i, k));
              }
            }
          }

          for (int k = j - 1; k >= 0; k--) {
            if (str[i][k] == '#')
              break;
            if (str[i][k] == '-' || str[i][k] == '|') {
              if (bs[1][mp[ii(i, k)]]) {
                if (bs[0][mp[ii(i, k)]])
                  s.insert(ii(i, k));
                found = true;
              }
            }
          }

          if (!found) {
            possible = false;
          }
        }
      }
    }

    for (map<ii, int>::iterator it = mp.begin(); it != mp.end(); it++) {
      ii xy = it->first;
      int x = xy.fi;
      int y = xy.se;

      if (bs[0][it->second] && !bs[1][it->second]) {
        str[x][y] = '|';
      } else if (!bs[0][it->second] && bs[1][it->second]) {
        str[x][y] = '-';
      }
    }

    cerr << "jml : " << SZ(s) << endl;
    if (possible) {
      bool found = false;
      for (ll i = 0; i < (1LL << SZ(s)); i++) {
        int C = 0;
        bool bs = true;
        for (set<ii>::iterator it = s.begin(); it != s.end(); it++) {
          ii xy = *it;
          int x = xy.fi;
          int y = xy.se;
          if (i & (1LL << C)) {
            str[x][y] = '-';
          } else {
            str[x][y] = '|';
          }
        }
        FOR(j, SZ(v)) {
          int x = v[j].fi;
          int y = v[j].se;
          bool f = false;
          for (int k = x - 1; k >= 0; k--) {
            if (str[k][y] == '#')
              break;
            if (str[k][y] == '|')
              f = true;
          }

          for (int k = x + 1; k < r; k++) {
            if (str[k][y] == '#')
              break;
            if (str[k][y] == '|')
              f = true;
          }

          for (int k = y - 1; k >= 0; k--) {
            if (str[x][k] == '#')
              break;
            if (str[x][k] == '-')
              f = true;
          }

          for (int k = y + 1; k < c; k++) {
            if (str[x][k] == '#')
              break;
            if (str[x][k] == '-')
              f = true;
          }
          if (!f) {
            bs = false;
            break;
          }
        }
        if (bs) {
          found = true;
          break;
        }
      }
      if (!found)
        possible = false;
    }

    printf("Case #%d: %s\n", ctr, possible ? "POSSIBLE" : "IMPOSSIBLE");
    if (possible)
      FOR(i, r) printf("%s\n", str[i]);
    cerr << "Test " << ctr << " done \n";
  }
  return 0;
}
