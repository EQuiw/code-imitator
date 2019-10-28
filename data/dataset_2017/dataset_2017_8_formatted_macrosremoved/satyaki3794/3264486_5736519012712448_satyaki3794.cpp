// satyaki3794
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> ii;

ll pwr(ll base, ll p, ll mod = (1000000007LL)) {
  ll ans = 1;
  while (p) {
    if (p & 1)
      ans = (ans * base) % mod;
    base = (base * base) % mod;
    p /= 2;
  }
  return ans;
}

ll gcd(ll a, ll b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

int main() {

  ios_base::sync_with_stdio(0);
  cin.tie(0);

  freopen("A-small-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t, x = 1;
  cin >> t;
  while (t--) {

    string str;
    cin >> str;

    int k;
    cin >> k;

    int n = (int)str.length(), ans = 0;
    for (int i = 0; i + k - 1 < n; i++)
      if (str[i] == '-') {
        ans++;
        for (int j = i; j < i + k; j++)
          if (str[j] == '-')
            str[j] = '+';
          else
            str[j] = '-';
      }

    for (int i = 0; i < n; i++)
      if (str[i] == '-')
        ans = -1;

    if (ans == -1)
      cout << "Case #" << x++ << ": IMPOSSIBLE" << endl;
    else
      cout << "Case #" << x++ << ": " << ans << endl;
  }

  return 0;
}
