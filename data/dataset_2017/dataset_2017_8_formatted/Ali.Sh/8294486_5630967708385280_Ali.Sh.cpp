#include <bits/stdc++.h>

#define F first
#define S second
#define pb push_back
#define ld long double
#define ll long long
#define int long long

using namespace std;

const int MAXN = 101 * 1001;

#define cin fin
#define cout fout
ifstream fin("in.in");
ofstream fout("out.out");

int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  cout << fixed << setprecision(6);
  for (int _ = 1; _ <= t; _++) {
    int n;
    ld d;
    cin >> d >> n;
    ld lst = 0.;
    for (int i = 0; i < n; i++) {
      ld x, v;
      cin >> x >> v;
      lst = max(lst, (d - x) / v);
    }
    cout << "Case #" << _ << ": " << d / lst << '\n';
  }
}
