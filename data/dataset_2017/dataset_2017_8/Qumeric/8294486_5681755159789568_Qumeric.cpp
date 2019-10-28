#include<bits/stdc++.h>

#define DIST first
#define SPEED second

using namespace std;

typedef long long ll;
typedef long double ld;

ll t, n, q;

ll calcd(vector<ll>& d, ll a, ll b) {
  ll r = 0;
  for (int i = a; i < b; i++)
    r += d[i];
  return r;
}

void solve() {
    cin >> n >> q;
    vector<pair<ll, ll>> horses(n);
    vector<ll> d(n-1);
    for (int i = 0; i < n; i++) {
      cin >> horses[i].DIST >> horses[i].SPEED;
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        int a; cin >> a;
        if (a == -1)
          continue;
        d[i] = a;
      }
    }
    ll tmp; cin >> tmp >> tmp;

    vector<ld> dp(n, 1e18);
    dp[0] = 0;

    for (int i = 0; i < n-1; i++) {
      ll hd = horses[i].DIST;
      ll j = i;
      ll rd = 0;
      while(hd >= d[j] && j < n-1) {
        rd++;
        hd -= d[j];
        j++;
      }
      horses[i].DIST = rd;
    }

    /*for (int i = 0; i < n; i++) {
      cerr << "HORSE #" << i << " DIST IS " << horses[i].DIST << endl;
    }*/

    for (int i = 0; i < n; i++) {
      for (int j = i+1; j < min(i+horses[i].DIST+1, n); j++) {
        dp[j] = min(dp[j], dp[i]+((ld)calcd(d, i, j)/horses[i].SPEED));
        //cerr << "NEW DP[" << j << "] IS " << dp[j] << endl;
      }
    }
    cout << fixed << dp[n-1] << endl;
}

int main() {
  ios::sync_with_stdio(0);
  cout.precision(10);
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
}
