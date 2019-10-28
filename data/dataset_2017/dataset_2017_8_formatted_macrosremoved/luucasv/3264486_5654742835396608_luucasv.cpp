#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
  ios::sync_with_stdio(0);
  int t, cas = 1;
  cin >> t;
  while (t--) {
    map<ll, ll, greater<ll>> mp;
    cout << "Case #" << cas++ << ": ";
    ll n, k;
    cin >> n >> k;
    mp[n] = 1;
    ll ls = 0;
    while (k > 0) {
      ls = mp.begin()->first;
      ll q = mp.begin()->second;
      mp.erase(mp.begin());
      mp[ls / 2] += q;
      mp[(ls - 1) / 2] += q;
      k -= q;
    }
    cout << ls / 2 << " " << (ls - 1) / 2 << endl;
  }
}
