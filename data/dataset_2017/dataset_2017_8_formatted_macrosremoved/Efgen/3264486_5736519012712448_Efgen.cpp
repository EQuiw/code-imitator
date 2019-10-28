#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<vector<int>> vvi;
typedef vector<ll> vl;
typedef vector<vector<ll>> vvl;

int main() {
  int tests;
  cin >> tests;
  for (int test = 1; test <= tests; test++) {
    cout << "Case #" << test << ": ";
    string s;
    int k;
    cin >> s >> k;
    int n = s.size();
    vector<bool> a(n);
    for (int i = 0; i < (int)(n); i++)
      a[i] = s[i] == '+';
    int res = 0;
    for (int i = 0; i < (int)(n - k + 1); i++) {
      if (!a[i]) {
        res++;
        for (int j = 0; j < (int)(k); j++) {
          a[i + j] = !a[i + j];
        }
      }
    }
    bool ok = true;
    for (int i = 0; i < (int)(k); i++)
      ok &= a[n - i - 1];
    if (ok)
      cout << res;
    else
      cout << "IMPOSSIBLE";
    cout << endl;
  }
}
