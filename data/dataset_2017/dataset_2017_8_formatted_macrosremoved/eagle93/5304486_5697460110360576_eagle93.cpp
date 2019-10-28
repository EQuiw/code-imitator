#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;
typedef unsigned long long ull;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;

const int OO = (int)2e9;
const double eps = 1e-9;

const int N = 55;
const ll M = 1000000;

int n, p;
ll r[N];
ll a[N][N];

int solve1() {
  int res = 0;
  for (int i = 0; i < p; i++) {
    ll st = 1, en = M;
    while (st < en) {
      ll mid = st + (en - st) / 2;
      ll v = mid * r[0];
      ll v90 = v * 90;
      ll v110 = v * 110;
      if (v110 < a[0][i])
        st = mid + 1;
      else
        en = mid;
    }
    ll v = st * r[0];
    ll v90 = v * 90;
    ll v110 = v * 110;
    if (a[0][i] >= v90 && a[0][i] <= v110) {
      res++;
    }
  }
  return res;
}

bool valid(ll p0, ll p1) {
  ll st = 1, en = M;
  while (st < en) {
    ll mid = st + (en - st) / 2;
    ll v0 = mid * r[0];
    ll v1 = mid * r[1];
    ll v090 = v0 * 90;
    ll v0110 = v0 * 110;
    ll v190 = v1 * 90;
    ll v1110 = v1 * 110;
    if (v0110 < p0 && v1110 < p1) // not sure
      st = mid + 1;
    else
      en = mid;
  }
  for (ll mid = st;; mid++) {
    ll v0 = mid * r[0];
    ll v1 = mid * r[1];
    ll v090 = v0 * 90;
    ll v0110 = v0 * 110;
    ll v190 = v1 * 90;
    ll v1110 = v1 * 110;
    if (p0 >= v090 && p0 <= v0110 && p1 >= v190 && p1 <= v1110) {
      return 1;
    }
    if (v090 > p0 || v190 > p1)
      break;
  }
  return 0;
}

int dp[1 << 8][1 << 8];
int vis[1 << 8][1 << 8];
int vid;

int calc(int msk0, int msk1) {
  int &ret = dp[msk0][msk1];
  if (vis[msk0][msk1] == vid)
    return ret;
  vis[msk0][msk1] = vid;
  ret = 0;
  for (int i0 = 0; i0 < p; i0++) {
    if (!(msk0 & (1 << i0))) {
      for (int i1 = 0; i1 < p; i1++) {
        if (!(msk1 & (1 << i1))) {
          if (valid(a[0][i0], a[1][i1])) {
            ret = max(ret, 1 + calc(msk0 | (1 << i0), msk1 | (1 << i1)));
          }
        }
      }
    }
  }
  return ret;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  //#ifndef ONLINE_JUDGE
  freopen("B-small-attempt3.in", "rt", stdin);
  freopen("out.txt", "wt", stdout);
  //#endif
  int t, tt = 1;
  cin >> t;
  while (t--) {
    cin >> n >> p;
    for (int i = 0; i < n; i++) {
      cin >> r[i];
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++) {
        cin >> a[i][j];
        a[i][j] *= 100;
      }
    }
    int res = 0;
    if (n == 1)
      res = solve1();
    else {
      vid++;
      res = calc(0, 0);
    }
    cout << "Case #" << tt++ << ": " << res << "\n";
  }
  return 0;
}
