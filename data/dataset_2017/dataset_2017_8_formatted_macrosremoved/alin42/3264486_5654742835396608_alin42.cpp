#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

map<ll, ll> freq;
int main() {
  ios::sync_with_stdio(0);
  freopen("readable.txt", "w", stdout);
  int t;
  cin >> t;
  for (int ca = 1; ca <= t; ca++) {
    cout << "Case #" << ca << ": ";
    ll n, k;
    cin >> n >> k;
    freq.clear();
    set<ll> q;
    q.insert(-n);
    freq[n] = 1;
    vector<pair<ll, ll>> vals;
    while (q.size()) {
      ll now = -(*q.begin());
      q.erase(q.begin());
      ll val = freq[now];
      // cout<<now<<" "<<val<<endl;
      vals.push_back({-now, val});
      ll l = (now - 1) / 2;
      ll r = now - 1 - l;
      if (l != 0) {
        if (freq.count(l))
          freq[l] += val;
        else {
          freq[l] = val;
          q.insert(-l);
        }
      }
      if (r != 0) {
        if (freq.count(r))
          freq[r] += val;
        else {
          freq[r] = val;
          q.insert(-r);
        }
      }
    }
    sort(vals.begin(), vals.end());
    ll tot = 0;
    for (pair<ll, ll> p : vals) {
      tot += p.second;
      if (tot >= k) {
        ll l = (-p.first - 1) / 2;
        ll r = -p.first - 1 - l;
        cout << r << " " << l << endl;
        break;
      }
    }
  }
  return 0;
}

// g++ -std=c++11 -O2 -Wfatal-errors -Im -Wall -Wextra -o "output.txt"
// "code.cpp"
