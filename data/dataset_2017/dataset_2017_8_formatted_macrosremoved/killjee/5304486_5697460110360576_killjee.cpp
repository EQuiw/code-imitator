#include <bits/stdc++.h>
using namespace std;

typedef int ll;
typedef pair<long long, long long> pii;
typedef pair<long long, pair<long long, long long>> piii;

const long long mod = 1e9 + 7;
long double eps = 0.000001;

long long POWER[65];
long long power(long long a, long long b) {
  long long ret = 1;
  while (b) {
    if (b & 1)
      ret *= a;
    a *= a;
    if (ret >= mod)
      ret %= mod;
    if (a >= mod)
      a %= mod;
    b >>= 1;
  }
  return ret;
}
long long inv(long long x) { return power(x, mod - 2); }

void precompute() {
  POWER[0] = 1;
  for (long long i = 1; i < 63; i++)
    POWER[i] = POWER[i - 1] << 1LL;
}

vector<long long> v, v1[3];
long long n, p;

bool cmp(long double a, long double b) {
  if (a - b > eps)
    return 1;
  return 0;
}

long long DP[1 << 9][1 << 9];
long long go(long long mask, long long mask1) {
  // cout<<mask<<" "<<mask1<<endl;
  long long ret = 0;
  if (DP[mask][mask1] != -1)
    return DP[mask][mask1];
  for (long long i = 0; i < p; i++) {
    if (mask & (1 << i))
      continue;
    for (long long j = 0; j < p; j++) {
      if (mask1 & (1 << j))
        continue;
      // double l=v[0]*0.9,h=v[0]*1.1;
      long long lo = 0, hi = 1e7, mi = 0, ma = 0, ans = 0;
      while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        long double a = mid * 9 * v[0], b = mid * 11 * v[0];
        // cout<<a<<" "<<v1[0][i]<<" "<<b<<endl;
        if (a > v1[0][i] * 10) {

          hi = mid - 1;
        } else if (10 * v1[0][i] > b) {
          lo = mid + 1;
        } else {
          ans = mid;
          hi = mid - 1;
        }
      }
      mi = ans;
      ans = 0;
      lo = 0, hi = 1e7;
      while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        long double a = mid * 9 * v[0], b = mid * 11 * v[0];
        if (a > 10 * v1[0][i]) {

          hi = mid - 1;
        } else if (v1[0][i] * 10 > b) {
          lo = mid + 1;
        } else {
          ans = mid;
          lo = mid + 1;
        }
      }
      ma = ans;
      ans = 0;
      lo = 0, hi = 1e7;
      while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        long double a = mid * 9 * v[1], b = mid * 11 * v[1];
        if (a > v1[1][j] * 10) {

          hi = mid - 1;
        } else if (10 * v1[1][j] > b) {
          lo = mid + 1;
        } else {
          ans = mid;
          hi = mid - 1;
        }
      }
      long long mi1 = ans;
      ans = 0;
      lo = 0, hi = 1e7;
      while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        long double a = mid * 9 * v[1], b = mid * 11 * v[1];
        if (a > 10 * v1[1][j]) {

          hi = mid - 1;
        } else if (10 * v1[1][j] > b) {
          lo = mid + 1;
        } else {
          ans = mid;
          lo = mid + 1;
        }
      }
      long long ma1 = ans;

      // cout<<i<<" "<<j<<" "<<mi<<" "<<ma<<" "<<mi1<<" "<<ma1<<endl;

      if (mi > ma1 || mi1 > ma)
        continue;
      if (ma == 0 || ma1 == 0)
        continue;
      ret = max(ret, 1 + go(mask | (1 << i), mask1 | (1 << j)));
      // cout<<ret<<endl;
    }
  }
  DP[mask][mask1] = ret;
  return ret;
}

ll main() {
  freopen("Task.in", "r", stdin);
  freopen("Task.out", "w", stdout);
  long long t, cc = 0;
  cin >> t;

  while (t--) {
    memset(DP, -1, sizeof(DP));
    v.clear();
    v1[0].clear();
    v1[1].clear();
    cin >> n >> p;

    for (long long i = 0; i < n; i++) {
      long long x;
      cin >> x;

      v.push_back(x);
    }

    for (long long i = 0; i < n; i++) {
      for (long long j = 0; j < p; j++) {
        long long x;
        cin >> x;

        v1[i].push_back(x);
      }
    }

    if (n == 1) {
      long long cnt = 0;
      for (long long i = 0; i < p; i++) {
        long long l = v[0] * 9, h = v[0] * 11;
        long long lo = 0, hi = 1e7, mi = 0, ma = 0, ans = 0;
        while (lo <= hi) {
          long long mid = (lo + hi) / 2;
          long long a = mid * l, b = mid * h;
          // cout<<a<<" "<<v1[0][i]<<" "<<b<<endl;
          if (a > 10 * v1[0][i]) {

            hi = mid - 1;
          } else if (10 * v1[0][i] > b) {
            lo = mid + 1;
          } else {
            ans = mid;
            hi = mid - 1;
          }
        }
        mi = ans;
        ans = 0;
        lo = 0, hi = 1e7;
        while (lo <= hi) {
          long long mid = (lo + hi) / 2;
          long long a = mid * l, b = mid * h;
          if (a > v1[0][i] * 10) {

            hi = mid - 1;
          } else if (v1[0][i] * 10 > b) {
            lo = mid + 1;
          } else {
            ans = mid;
            lo = mid + 1;
          }
        }
        ma = ans;
        if (ma < mi || ma == 0)
          continue;
        cnt++;
      }
      ++cc;
      cout << "Case #" << cc << ": " << cnt << endl;
      continue;
    }
    ++cc;
    cout << "Case #" << cc << ": " << go(0, 0) << endl;
  }
}
