#include <bits/stdc++.h>
using namespace std;

const long long MAXN = 1001 * 1001, MOD = 1e9 + 7;

long long n;

vector<long long> a, b;

void f(long long x, vector<long long> &a) {
  a.clear();
  while (x) {
    a.push_back(x % 10);
    x /= 10;
  }
  reverse(a.begin(), a.end());
}

bool check(long long X) {
  f(X, a);
  if (a.size() < b.size())
    return 1;
  long long x = 0;
  for (auto &u : a) {
    u = max(u, x);
    x = u;
  }
  reverse(a.begin(), a.end());
  x = 0;
  long long t = 1;
  for (auto u : a) {
    x += u * t;
    t *= 10;
  }
  return x <= n;
}

int32_t main() {
  ios::sync_with_stdio(0);
  long long t;
  cin >> t;
  for (long long _ = 1; _ <= t; _++) {
    cin >> n;
    f(n, b);
    long long l = 1, r = n + 1;
    while (r - l > 1) {
      long long mid = (l + r) / 2;
      if (check(mid))
        l = mid;
      else
        r = mid;
    }
    cout << "Case #" << _ << ": " << l << '\n';
  }
}
