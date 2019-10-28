#include <bits/stdc++.h>
using namespace std;

const long long MAXN = 33, MOD = 1e9 + 7;

char s[MAXN][MAXN], t[MAXN][MAXN];

char prv[MAXN];

void solve() {
  long long n, m;
  cin >> n >> m;
  memset(t, 0, sizeof t);
  memset(prv, 0, sizeof prv);
  for (long long i = 0; i < n; i++)
    for (long long j = 0; j < m; j++)
      cin >> s[i][j], prv[i] = (s[i][j] == '?' ? prv[i] : s[i][j]);
  for (long long i = 0; i < n; i++) {
    if (!prv[i])
      continue;
    char ch = prv[i];
    for (long long j = m - 1; j > -1; j--) {
      if (s[i][j] != '?')
        ch = s[i][j];
      t[i][j] = ch;
    }
  }
  for (long long x = 0; x < 100; x++) {
    for (long long i = 0; i < n - 1; i++) {
      if (!(t[i][0] == 0 && t[i + 1][0] != 0))
        continue;
      for (long long j = 0; j < m; j++)
        t[i][j] = t[i + 1][j];
    }

    for (long long i = n - 1; i; i--) {
      if (!(t[i][0] == 0 && t[i - 1][0] != 0))
        continue;
      for (long long j = 0; j < m; j++)
        t[i][j] = t[i - 1][j];
    }
  }
  // acout << m  << endl ;
  for (long long i = 0; i < n; i++, cout << '\n')
    for (long long j = 0; j < m; j++)
      cout << t[i][j];
}

int32_t main() {
  ios::sync_with_stdio(0);
  long long t;
  cin >> t;
  for (long long _ = 1; _ <= t; _++) {
    cout << "Case #" << _ << ":" << '\n';
    solve();
  }
}
