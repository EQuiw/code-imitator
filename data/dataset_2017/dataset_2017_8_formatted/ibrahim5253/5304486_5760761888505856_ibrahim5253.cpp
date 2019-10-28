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
#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define umap unordered_map
#define ff first
#define ss second
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
    int r, c;
    cin >> r >> c;
    vector<vector<pii>> v;
    string cake[r];
    for (int i = 0; i < r; ++i)
      cin >> cake[i];
    for (int i = 0; i < r; ++i) {
      vector<pii> vec;
      for (int j = 0; j < c; ++j)
        if (cake[i][j] != '?')
          vec.pb(mp(i, j));
      if (!vec.empty())
        v.pb(vec);
    }
    int sr = 0;
    int L = v.size();
    for (int i = 0; i < L; ++i) {
      int er = (i == L - 1 ? r - 1 : v[i][0].ff);
      int l = v[i].size();
      int sc = 0;
      for (int j = 0; j < l; ++j) {
        int ec = (j == l - 1 ? c - 1 : v[i][j].ss);
        for (int x = sr; x <= er; ++x)
          for (int y = sc; y <= ec; ++y)
            cake[x][y] = cake[v[i][j].ff][v[i][j].ss];
        sc = v[i][j].ss + 1;
      }
      sr = v[i][0].ff + 1;
    }
    cout << "Case #" << i << ":\n";
    for (int i = 0; i < r; ++i)
      cout << cake[i] << "\n";
  }
  return 0;
}
