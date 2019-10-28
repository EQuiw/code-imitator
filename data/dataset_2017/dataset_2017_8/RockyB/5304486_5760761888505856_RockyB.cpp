#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>

#define f first
#define s second

#define pb push_back
#define pp pop_back
#define mp make_pair

#define sz(x) (int)x.size()
#define sqr(x) ((x) * 1ll * (x))
#define all(x) x.begin(), x.end()

#define rep(i, l, r) for (int i = l; i <= r; i++)
#define per(i, l, r) for (int i = l; i >= r; i--)

#define dbg(x) cerr << (#x) << " --> " << (x) << nl;
#define Kazakhstan ios_base :: sync_with_stdio(0), cin.tie(0), cout.tie(0);

#define nl '\n'
#define ioi exit(0);

#define _3day "A-small-attempt1"

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef tree < pair <int, int>, null_type, less < pair <int, int> >, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int N = 1e6 + 7, inf = 1e9 + 7, mod = 1e9 + 7;
const ll linf = (ll)1e18 + 7;
const int dx[] = {-1, 0, 1, 0, 1, -1, -1, 1}, dy[] = {0, 1, 0, -1, 1, -1, 1, -1};


int n, m;
char c[33][33], cur[33][33];

struct node {
  int x1, y1, x2, y2;
  node() {}
  node(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
} a[26];
bool cmp(char x, char y) {
  return a[x - 'a'].x2 > a[y - 'a'].x2;
}
int get(int x) {
  return ((rand() << 16) + rand()) % x + 1;
}
void gen() {
  n = get(25), m = get(25);

  set <char> st;
  rep(i, 1, n) {
    rep(j, 1, m) {
      char x = get(26) - 1;
      if (st.count(x)) c[i][j] = '?';
      else c[i][j] = x + 'A';
      st.insert(x);
    }
  }

}
void solve(int _id) {
  cin >> n >> m;
  //gen();
  vector <char> v;
  rep(i, 1, n) {
    rep(j, 1, m) {
      cin >> c[i][j];
      cur[i][j] = c[i][j];
      if (isalpha(c[i][j])) a[c[i][j] - 'a'] = node(i, j, i, j), v.pb(c[i][j]);
    }
  //  cout << nl;
  }

  sort(all(v), cmp);
  rep(blin, 1, 10000) {
    for (auto z : v) {
      int u = a[z - 'a'].x1, l = a[z - 'a'].y1, r = a[z - 'a'].y2;
      per(i, u - 1, 1) {
        bool good = 1;
        rep(j, l, r)
          if (isalpha(c[i][j])) {
            good = 0;
            break;
          }
        if (!good) break;
        rep(j, l, r) c[i][j] = z;
        a[z - 'a'].x1 = i;
      }
      int d = a[z - 'a'].x2;
      rep(i, d + 1, n) {
        bool good = 1;
        rep(j, l, r)
          if (isalpha(c[i][j])) {
            good = 0;
            break;
          }
        if (!good) break;
        rep(j, l, r) c[i][j] = z;
        a[z - 'a'].x2 = i;
      }
      u = a[z - 'a'].x1, d = a[z - 'a'].x2;
      rep(i, r + 1, m) {
        bool good = 1;
        rep(j, u, d)
          if (isalpha(c[j][i])) {
            good = 0;
            break;
          }
        if (!good) break;
        rep(j, u, d) c[j][i] = z;
        a[z - 'a'].y2 = i;
      }
      per(i, l - 1, 1) {
        bool good = 1;
        rep(j, u, d)
          if (isalpha(c[j][i])) {
            good = 0;
            break;
          }
        if (!good) break;
        rep(j, u, d) c[j][i] = z;
        a[z - 'a'].y1 = i;
      }
    }
    bool good = 1;
    rep(i, 1, n)
      rep(j, 1, m) {
        if (c[i][j] == '?') {
          good = 0;
          break;
        }
      }
    if (good) break;
    rep(i, 1, n)
      rep(j, 1, m)
        c[i][j] = cur[i][j];
    random_shuffle(all(v));
  }

  cout << "Case #" << _id << ":\n";
  rep(i, 1, n) {
    rep(j, 1, m) {
      cout << c[i][j];
      assert(c[i][j] != '?');
    }
    cout << nl;
  }
}

int T;
int main() {
  #ifndef _3day
    freopen (_3day".in", "r", stdin);
    freopen (_3day".out", "w", stdout);
  #endif

  //Kazakhstan
  srand(time(0));
  cin >> T;
  rep(i, 1, T)
    solve(i);
  ioi
}
