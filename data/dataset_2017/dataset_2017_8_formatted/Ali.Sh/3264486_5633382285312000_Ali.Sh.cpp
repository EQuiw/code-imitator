#include <bits/stdc++.h>

#define int long long
#define ll long long
#define F first
#define S second
#define pb push_back
#define ld double

using namespace std;

const int MAXN = 1001 * 1001, MOD = 1e9 + 7;

int n;

vector<int> a, b;

void f(int x, vector<int> &a) {
  a.clear();
  while (x) {
    a.pb(x % 10);
    x /= 10;
  }
  reverse(a.begin(), a.end());
}

bool check(int X) {
  f(X, a);
  if (a.size() < b.size())
    return 1;
  int x = 0;
  for (auto &u : a) {
    u = max(u, x);
    x = u;
  }
  reverse(a.begin(), a.end());
  x = 0;
  int t = 1;
  for (auto u : a) {
    x += u * t;
    t *= 10;
  }
  return x <= n;
}

int32_t main() {
  ios::sync_with_stdio(0);
  int t;
  cin >> t;
  for (int _ = 1; _ <= t; _++) {
    cin >> n;
    f(n, b);
    int l = 1, r = n + 1;
    while (r - l > 1) {
      int mid = (l + r) / 2;
      if (check(mid))
        l = mid;
      else
        r = mid;
    }
    cout << "Case #" << _ << ": " << l << '\n';
  }
}
