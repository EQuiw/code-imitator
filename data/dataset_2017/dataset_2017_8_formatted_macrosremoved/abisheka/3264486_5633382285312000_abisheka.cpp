#include <algorithm>
#include <bitset>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<vector<ll>> mat;

int main() {
  ios_base::sync_with_stdio(false);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t, t1 = 0;
  cin >> t;
  vector<long long int> v;
  ll x = 1;
  for (int i = 1; i <= 19; i++) {
    v.push_back(x);
    x = x * 10 + 1;
  }
  while (t--) {
    t1++;
    cout << "Case #";
    cout << t1;
    cout << ": ";

    ll n;
    cin >> n;
    ll ans = 0;
    for (int i = 1; i <= 9; i++) {
      int sz = v.size();
      for (int j = sz - 1; j >= 0; j--) {
        if (v[j] <= n) {
          n -= v[j];
          ans += v[j];
          break;
        }
      }
    }
    cout << ans;
    cout << "\n";
  }
  return 0;
}
