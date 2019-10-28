#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll;
typedef long double ld;

bool flip[13131];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T, n, k;
  cin >> T;
  string s;
  for (int it = 0; it < T; it++) {
    cin >> s >> k;
    n = s.size();
    bool bit = 0;
    int ans = 0;
    memset(flip, 0, sizeof flip);
    for (int i = 0; i < n - k + 1; i++) {
      bit ^= flip[i];
      if (!(bit ^ (s[i] == '+')))
        bit ^= 1, ans++, flip[i + k] = 1;
    }
    bool pos = 1;
    for (int i = n - k + 1; i < n; i++) {
      bit ^= flip[i];
      if (!(bit ^ (s[i] == '+')))
        pos = 0;
    }
    cout << "Case #" << it + 1 << ": ";
    if (pos)
      cout << ans << endl;
    else
      cout << "IMPOSSIBLE" << endl;
  }
}
