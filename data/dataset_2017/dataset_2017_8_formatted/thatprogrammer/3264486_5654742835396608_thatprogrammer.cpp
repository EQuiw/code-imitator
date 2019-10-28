// Hi
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;
ll a, b;
void solve(ll n, ll k) {
  map<ll, ll> prev;
  map<ll, ll> cur;

  prev[n] = 1;
  while (true) {
    for (map<ll, ll>::reverse_iterator it = prev.rbegin(); it != prev.rend();
         ++it) {
      // split
      // check if done

      a = ((it->first) - 1) / 2;
      b = (it->first) - 1 - a;
      ll val = it->second;
      k -= val;
      if (k <= 0)
        return;
      if (a != 0)
        cur[a] += val;
      if (b != 0)
        cur[b] += val;
    }
    prev.swap(cur);
    cur.clear();
  }
}
int main() {
  ios::sync_with_stdio(false);
  freopen("test.txt", "r", stdin);
  freopen("test1.txt", "w", stdout);
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    ll n, k;
    cin >> n >> k;
    solve(n, k);

    cout << "Case #" << i << ": " << max(a, b) << " " << min(a, b) << endl;
  }
}
