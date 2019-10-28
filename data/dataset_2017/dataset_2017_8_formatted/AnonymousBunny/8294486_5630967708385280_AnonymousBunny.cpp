#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define mp make_pair
#define F first
#define S second
const int mod = 1e9 + 7;
#define maxn 1020

int k[maxn], s[maxn];

bool check(int n, double sp, int d) {
  for (int i = 1; i <= n; i++) {
    if ((double)d / sp < (double)(d - k[i]) / (double)s[i])
      return 0;
  }
  return 1;
}

void solve(int ind) {
  int d, n;
  cin >> d >> n;
  for (int i = 1; i <= n; i++)
    cin >> k[i] >> s[i];
  double lo = 0, hi = 1e16;
  for (int i = 0; i < 100; i++) {
    double mid = (lo + hi) / 2.000;
    if (check(n, mid, d)) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  cout << "Case #" << ind << ": ";
  double mid = (lo + hi) / 2.000;
  printf("%.6f \n", mid);
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++)
    solve(i);
  return 0;
}