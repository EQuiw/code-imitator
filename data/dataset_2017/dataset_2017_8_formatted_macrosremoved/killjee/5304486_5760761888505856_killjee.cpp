#include <bits/stdc++.h>
using namespace std;

typedef int ll;
typedef pair<long long, long long> pii;
typedef pair<long long, pair<long long, long long>> piii;

const long long mod = 1e9 + 7;

long long POWER[65];
long long power(long long a, long long b) {
  long long ret = 1;
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
long long inv(long long x) { return power(x, mod - 2); }

void precompute() {
  POWER[0] = 1;
  for (long long i = 1; i < 63; i++)
    POWER[i] = POWER[i - 1] << 1LL;
}

vector<string> v;
ll main() {
  freopen("Task.in", "r", stdin);
  freopen("Task.out", "w", stdout);
  long long t, cc = 0;
  cin >> t;

  while (t--) {
    v.clear();
    long long r, c;
    cin >> r >> c;

    for (long long i = 0; i < r; i++) {
      string s;
      cin >> s;
      v.push_back(s);
    }

    for (long long i = 0; i < v.size(); i++) {
      bool ch = 0;
      char c;
      for (long long j = 0; j < v[i].size(); j++) {
        if (v[i][j] != '?' && !ch) {
          c = v[i][j];
          for (long long k = 0; k < j; k++) {
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
    for (long long i = 0; i < v.size(); i++) {
      if (v[i][0] == '?')
        continue;
      for (long long j = i - 1; j >= 0; j--) {
        if (v[j][0] != '?')
          break;
        for (long long k = 0; k < v[j].size(); k++) {
          v[j][k] = v[j + 1][k];
        }
      }
      for (long long j = i + 1; j < v.size(); j++) {
        if (v[j][0] != '?')
          break;
        for (long long k = 0; k < v[j].size(); k++) {
          v[j][k] = v[j - 1][k];
        }
      }
    }
    ++cc;
    cout << "Case #" << cc << ": \n";
    for (long long i = 0; i < v.size(); i++)
      cout << v[i] << endl;
  }
}
