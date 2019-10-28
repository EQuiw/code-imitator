#include <bits/stdc++.h>

#define int long long
#define ll long long
#define F first
#define S second
#define pb push_back
#define ld double

using namespace std;

const int MAXN = 33, MOD = 1e9 + 7;

char s[MAXN][MAXN], t[MAXN][MAXN];

char prv[MAXN];

void solve() {
  int n, m;
  cin >> n >> m;
  memset(t, 0, sizeof t);
  memset(prv, 0, sizeof prv);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> s[i][j], prv[i] = (s[i][j] == '?' ? prv[i] : s[i][j]);
  for (int i = 0; i < n; i++) {
    if (!prv[i])
      continue;
    char ch = prv[i];
    for (int j = m - 1; j > -1; j--) {
      if (s[i][j] != '?')
        ch = s[i][j];
      t[i][j] = ch;
    }
  }
  for (int x = 0; x < 100; x++) {
    for (int i = 0; i < n - 1; i++) {
      if (!(t[i][0] == 0 && t[i + 1][0] != 0))
        continue;
      for (int j = 0; j < m; j++)
        t[i][j] = t[i + 1][j];
    }

    for (int i = n - 1; i; i--) {
      if (!(t[i][0] == 0 && t[i - 1][0] != 0))
        continue;
      for (int j = 0; j < m; j++)
        t[i][j] = t[i - 1][j];
    }
  }
  // acout << m  << endl ;
  for (int i = 0; i < n; i++, cout << '\n')
    for (int j = 0; j < m; j++)
      cout << t[i][j];
}

int32_t main() {
  ios::sync_with_stdio(0);
  int t;
  cin >> t;
  for (int _ = 1; _ <= t; _++) {
    cout << "Case #" << _ << ":" << '\n';
    solve();
  }
}
