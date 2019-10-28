#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

//#define scd static_cast<double>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;
using pill = pair<int, ll>;
using vvi = vector<vi>;

ll gcd(ll a, ll b) {
  ll t;
  while ((t = a % b) != 0) {
    a = b;
    b = t;
  }
  return b;
}

ll fast_exp(ll base, ll n, ll m) {
  if (n == 0)
    return 1;
  ll t = fast_exp(base, n / 2, m);
  if (n % 2 == 0)
    return (t * t) % m;
  else
    return (((t * t) % m) * base) % m;
}

bool is_set(int i, ll mask) { return (mask >> i) & 1; }

int count_bits(ll mask) {
  int ans = 0;
  for (int i = 0; i < 64; ++i)
    if (is_set(i, mask))
      ++ans;
  return ans;
}

int first_bit(ll mask) {
  int i = 0;
  while (i < 64)
    if (is_set(i++, mask))
      return i - 1;
  return -1;
}

int main() {
  ios::sync_with_stdio(false);
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i) {
    int n, p;
    cin >> n >> p;
    ll w[n];
    for (int i = 0; i < n; ++i)
      cin >> w[i];
    pair<ll, ll> a[n][p];
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < p; ++j) {
        ll W;
        cin >> W;
        ll low = ceil(W / (w[i] * 1.1)), high = W / (w[i] * 0.9);
        a[i][j] = make_pair(low, high);
      }
    }
    if (n == 1) {
      int ans = 0;
      for (int i = 0; i < p; ++i)
        if (a[0][i].first <= a[0][i].second)
          ans++;
      cout << "Case #" << i << ": " << ans << "\n";
      continue;
    }
    int s[p];
    for (int i = 0; i < p; ++i)
      s[i] = i;
    int ans = 0;
    do {
      int val = 0;
      for (int i = 0; i < p; ++i) {
        if (a[0][i].first > a[0][i].second ||
            a[1][s[i]].first > a[1][s[i]].second)
          continue;
        if (a[0][i].first >= a[1][s[i]].first &&
                a[0][i].first <= a[1][s[i]].second ||
            a[1][s[i]].first >= a[0][i].first &&
                a[1][s[i]].first <= a[0][i].second)
          val++;
      }
      ans = max(ans, val);
    } while (next_permutation(s, s + p));
    cout << "Case #" << i << ": " << ans << "\n";
    /*        int ans=0;
            bool mark[n][p];
            memset(mark, false, sizeof mark);
            for (int i=0; i<p; ++i) {
                auto x=a[0][i];
                int count=0;
                for (int j=1; j<n; ++j) {
                    for (int k=0; k<p; ++k)
                        if (a[j][k].ff>=x.ff && a[j][k].ff<=x.ss ||
       x.ff>=a[j][k].ff && x.ff<=a[j][k].ss) { count++; mark[] break;
                        }
                }
            }*/
  }
  return 0;
}
