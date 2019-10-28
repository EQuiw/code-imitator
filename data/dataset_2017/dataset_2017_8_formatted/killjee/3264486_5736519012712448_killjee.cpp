#include <bits/stdc++.h>
using namespace std;

typedef int ll;

#define int long long
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define sz(x) ((int)x.size())
#define all(x) x.begin(), x.end()

typedef pair<int, int> pii;
typedef pair<int, pair<int, int>> piii;

const int mod = 1e9 + 7;

int POWER[65];
int power(int a, int b) {
  int ret = 1;
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
int inv(int x) { return power(x, mod - 2); }

void precompute() {
  POWER[0] = 1;
  for (int i = 1; i < 63; i++)
    POWER[i] = POWER[i - 1] << 1LL;
}

int a[1005];

ll main() {
  freopen("Task.in", "r", stdin);
  freopen("Task.out", "w", stdout);
  int t;
  cin >> t;
  int cc = 1;

  while (t--) {
    string s;
    int k;
    cin >> s >> k;

    for (int i = 0; i < sz(s); i++) {
      if (s[i] == '-')
        a[i] = 1;
      else
        a[i] = 0;
    }

    int cnt = 0;

    for (int i = sz(s) - 1; i >= 0; i--) {
      if (a[i] == 0)
        continue;
      if (i < k - 1)
        break;
      cnt++;
      for (int j = i, p = 0; p < k; p++, j--) {
        a[j] = (a[j] + 1) % 2;
      }
    }

    bool flag = 0;

    for (int i = 0; i < sz(s); i++) {
      // cout<<a[i]<<" ";
      if (a[i] == 1)
        flag = 1;
    }
    cout << "Case #" << cc << ": ";
    cc++;
    if (flag)
      cout << "Impossible\n";
    else
      cout << cnt << endl;
  }
}