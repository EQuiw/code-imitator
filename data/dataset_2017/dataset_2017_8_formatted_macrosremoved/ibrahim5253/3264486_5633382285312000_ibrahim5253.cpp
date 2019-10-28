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
    string n;
    cin >> n;
    char l = '0';
    int s = n.length();
    for (int j = 0; j < s; ++j) {
      if (n[j] < l) {
        --j;
        int k = j;
        while (k > 0 && n[k] == '1')
          n[k] = '9', --k;
        n[k] -= 1;
        while (k > 0 && n[k - 1] > n[k])
          n[k - 1] -= 1, n[k] = '9', --k;
        for (int x = j + 1; x < s; ++x)
          n[x] = '9';
        break;
      }
      l = n[j];
    }
    int k = 0;
    while (n[k] == '0')
      ++k;
    cout << "Case #" << i << ": " << n.substr(k) << "\n";
  }
  return 0;
}
