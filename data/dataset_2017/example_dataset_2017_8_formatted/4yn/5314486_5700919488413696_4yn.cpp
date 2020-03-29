#include <bits/stdc++.h>
using namespace std;

int tc;

int main() {
  cin >> tc;
  for (int t = 1; t <= tc; t++) {
    int n, p;
    cin >> n >> p;
    int g[109];
    int m[4];
    memset(m, 0, sizeof(m));
    for (int i = 0; i < n; i++) {
      cin >> g[i];
      m[g[i] % p]++;
    }
    int ans = m[0];
    int a;
    switch (p) {
    case 2:
      ans += m[1] / 2;
      m[1] = m[1] % 2;
      if (m[1])
        ans++;
      break;
    case 3:
      a = min(m[1], m[2]);
      m[1] -= a;
      m[2] -= a;
      ans += a;
      a = max(m[1], m[2]);
      ans += a / 3;
      a = a % 3;
      if (a)
        ans++;
      break;
    case 4:
      ans += m[2] / 2;
      m[2] = m[2] % 2;
      a = min(m[1], m[3]);
      m[1] -= a;
      m[2] -= a;
      ans += a;
      a = max(m[1], m[3]);
      ans += a / 3;
      a = a % 3;
      if (a)
        ans++;
      break;
    }
    cout << "Case #" << t << ": " << ans << endl;
  }
}