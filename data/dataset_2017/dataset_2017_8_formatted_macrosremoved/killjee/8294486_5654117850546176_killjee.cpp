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

long long ar[10055][3];
ll main() {
  freopen("Task.in", "r", stdin);
  freopen("Task.out", "w", stdout);

  long long cc = 1;
  long long t;
  cin >> t;
  while (t--) {
    memset(ar, 0, sizeof(ar));
    long long n, r, o, y, v, g, b;
    cin >> n >> r >> o >> y >> g >> b >> v;

    if (r > b && r > y) {
      for (long long i = 0; i < n - 1; i += 2) {
        if (r > 0) {
          ar[i][0] = 1;
          r--;
        }
      }
      for (long long i = 0; i < n; i += 2) {
        if (ar[i][0] == 0 && b > 0) {
          ar[i][1] = 1;
          b--;
        }
      }

      for (long long i = 1; i < n; i += 2) {
        if (ar[i][0] == 0 && ar[i][1] == 0 && ar[i][2] == 0) {
          if (b > 0) {
            ar[i][1] = 1;
            b--;
          } else if (y > 0) {
            ar[i][2] = 1;
            y--;
          }
        }
      }
      if (r > 0 || b > 0 || y > 0) {
        cout << "Case #" << cc << ": IMPOSSIBLE\n";
        cc++;
      } else {
        cout << "Case #" << cc << ": ";
        for (long long i = 0; i < n; i++) {
          // cout<<i<<" "<<ar[i][0]<<" "<<ar[i][2]<<" "<<ar[i][1]<<endl;
          if (ar[i][0] == 1) {
            cout << "R";
          }
          if (ar[i][1] == 1) {
            cout << "B";
          }
          if (ar[i][2] == 1) {
            cout << "Y";
          }
        }
        cout << endl;
        cc++;
      }
    } else if (b > r && b > y) {
      for (long long i = 0; i < n - 1; i += 2) {
        if (b > 0) {
          ar[i][0] = 1;
          b--;
        }
      }
      for (long long i = 0; i < n; i += 2) {
        if (ar[i][0] == 0 && r > 0) {
          ar[i][1] = 1;
          r--;
        }
      }

      for (long long i = 1; i < n; i += 2) {
        if (ar[i][0] == 0 && ar[i][1] == 0 && ar[i][2] == 0) {
          if (r > 0) {
            ar[i][1] = 1;
            r--;
          } else if (y > 0) {
            ar[i][2] = 1;
            y--;
          }
        }
      }
      if (r > 0 || b > 0 || y > 0) {
        cout << "Case #" << cc << ": IMPOSSIBLE\n";
        cc++;
      } else {
        cout << "Case #" << cc << ": ";
        for (long long i = 0; i < n; i++) {
          // cout<<i<<" "<<ar[i][0]<<" "<<ar[i][2]<<" "<<ar[i][1]<<endl;
          if (ar[i][1] == 1) {
            cout << "R";
          }
          if (ar[i][0] == 1) {
            cout << "B";
          }
          if (ar[i][2] == 1) {
            cout << "Y";
          }
        }
        cout << endl;
        cc++;
      }
    } else {
      for (long long i = 0; i < n - 1; i += 2) {
        if (y > 0) {
          ar[i][0] = 1;
          y--;
        }
      }
      for (long long i = 0; i < n; i += 2) {
        if (ar[i][0] == 0 && r > 0) {
          ar[i][1] = 1;
          r--;
        }
      }

      for (long long i = 1; i < n; i += 2) {
        if (ar[i][0] == 0 && ar[i][1] == 0 && ar[i][2] == 0) {
          if (r > 0) {
            ar[i][1] = 1;
            r--;
          } else if (b > 0) {
            ar[i][2] = 1;
            b--;
          }
        }
      }
      if (r > 0 || b > 0 || y > 0) {
        cout << "Case #" << cc << ": IMPOSSIBLE\n";
        cc++;
      } else {
        cout << "Case #" << cc << ": ";
        for (long long i = 0; i < n; i++) {
          // cout<<i<<" "<<ar[i][0]<<" "<<ar[i][2]<<" "<<ar[i][1]<<endl;
          if (ar[i][1] == 1) {
            cout << "R";
          }
          if (ar[i][0] == 1) {
            cout << "Y";
          }
          if (ar[i][2] == 1) {
            cout << "B";
          }
        }
        cout << endl;
        cc++;
      }
    }
  }
}
