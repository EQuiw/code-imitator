#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#define _USE_MATH_DEFINES
#include <complex>
#include <math.h>
using namespace std;
#if 1
#define ll long long
#else
#define ll int
#endif
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pb push_back
#define ft first
#define sd second
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, b, e) for (int i = b; i <= (int)(e); ++i)
#define FORR(i, b, e) for (int i = b; i >= (int)(e); --i)
#define Fill(a, b) memset(a, b, sizeof(a))
#define all(a) a.begin(), a.end()
template <typename T1, typename T2> void Max(T1 &a, T2 b) { a = max(a, (T1)b); }
template <typename T1, typename T2> void Min(T1 &a, T2 b) { a = min(a, (T1)b); }

const int inf = 1e9;
const int N = 50;

vector<pii> a[N];
double gram[N];

void solve() {
  int n, p;
  cin >> n >> p;
  rep(i, n) a[i].clear();
  rep(i, n) cin >> gram[i];

  rep(i, n) {
    double lo = gram[i] * 0.9;
    double hi = gram[i] * 1.1;

    rep(j, p) {
      double v;
      cin >> v;
      int t1 = floor(v / lo);
      int t2 = ceil(v / hi);
      if (t1 >= t2) {
        // cout << "t2 " << t2 << " t1 " << t1 << endl;
        a[i].push_back(pii(t2, t1));
        // cout << a[i].back().ft<<' '<<a[i].back().sd<< endl;
      }
    }
    // rep(j,a[i].size())cout<<a[i][j].ft<<' '<<a[i][j].sd<<''

    sort(all(a[i]));
    // for (auto e : a[i])cout << e.ft << ' ' << e.sd << ", ";
    // cout << endl;
  }

  vector<int> vec;
  for (auto e : a[0]) {
    FOR(i, e.ft, e.sd) vec.push_back(i);
    // vec.push_back(e.ft);
    // vec.push_back(e.sd);
  }
  sort(all(vec));
  int ans = 0;
  for (auto e : vec) {
    bool ok = 1;
    rep(i, n) {
      bool fd = 0;
      for (auto f : a[i]) {
        if (f.ft > e)
          break;
        if (f.ft <= e && f.sd >= e) {
          fd = 1;
          break;
        }
      }
      if (!fd) {
        ok = 0;
        break;
      }
    }
    if (ok) {
      ans++;
      rep(i, n) {
        for (auto &f : a[i]) {
          if (f.ft <= e && f.sd >= e) {
            f.ft = f.sd = 0;
            break;
          }
        }
      }
    }
  }

  cout << ans << endl;
}

void init() {}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  // freopen("C:\\Users\\LENOVO\\Documents\\Visual Studio
  // 2015\\Projects\\Test\\Input\\in.in", "r", stdin);

  init();
  int T;
  cin >> T;
  FOR(TI, 1, T) {
    cout << "Case #" << TI << ": ";
    // cout << "Case " << TI << ": ";
    solve();
  }

  return 0;
}
