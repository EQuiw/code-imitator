#define boost                                                                  \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL);
#define mod 1000000007
#define INF LLONG_MAX
#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define ll long long

int main() {

  boost;
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  ll t;
  cin >> t;
  for (ll ccr = 1; ccr <= t; ++ccr) {

    ll n, k, val1, val2;
    cin >> n >> k;
    priority_queue<ll, vector<ll>, less<ll>> pq;
    pq.push(n);
    while (k--) {
      ll val = pq.top();
      pq.pop();
      val1 = val2 = val / 2;
      if (val % 2 == 0) {
        --val2;
      }
      pq.push(val1);
      pq.push(val2);
    }

    cout << "Case #" << ccr << ": " << val1 << " " << val2 << "\n";
  }
  return 0;
}