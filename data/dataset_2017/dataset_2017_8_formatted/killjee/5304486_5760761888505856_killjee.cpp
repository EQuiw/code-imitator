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

vector<string> v;
ll main() {
  freopen("Task.in", "r", stdin);
  freopen("Task.out", "w", stdout);
  int t, cc = 0;
  cin >> t;

  while (t--) {
    v.clear();
    int r, c;
    cin >> r >> c;

    for (int i = 0; i < r; i++) {
      string s;
      cin >> s;
      v.pb(s);
    }

    for (int i = 0; i < v.size(); i++) {
      bool ch = 0;
      char c;
      for (int j = 0; j < v[i].size(); j++) {
        if (v[i][j] != '?' && !ch) {
          c = v[i][j];
          for (int k = 0; k < j; k++) {
            v[i][k] = c;
          }
          ch = 1;
          continue;
        }
        if (v[i][j] != '?') {
          c = v[i][j];
          continue;
        }
        if (ch)
          v[i][j] = c;
      }
    }
    for (int i = 0; i < v.size(); i++) {
      if (v[i][0] == '?')
        continue;
      for (int j = i - 1; j >= 0; j--) {
        if (v[j][0] != '?')
          break;
        for (int k = 0; k < v[j].size(); k++) {
          v[j][k] = v[j + 1][k];
        }
      }
      for (int j = i + 1; j < v.size(); j++) {
        if (v[j][0] != '?')
          break;
        for (int k = 0; k < v[j].size(); k++) {
          v[j][k] = v[j - 1][k];
        }
      }
    }
    ++cc;
    cout << "Case #" << cc << ": \n";
    for (int i = 0; i < v.size(); i++)
      cout << v[i] << endl;
  }
}