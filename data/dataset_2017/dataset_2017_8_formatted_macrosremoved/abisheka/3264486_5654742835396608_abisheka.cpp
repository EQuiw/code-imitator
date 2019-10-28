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
  while (t--) {
    t1++;
    cout << "Case #";
    cout << t1;
    cout << ": ";
    ll n, k;
    cin >> n >> k;
    ll c = 0, cool;
    map<ll, ll> m;
    m[n] = 1;
    while (1) {
      map<ll, ll>::iterator it = m.end();
      it--;
      ll no = it->first, cnt = it->second;
      m.erase(it);
      if (no == 1) {
        cool = no;
        break;
      }
      if (c + cnt >= k) {
        cool = no;
        break;
      }
      c += cnt;
      if (no % 2 == 0) {
        m[no / 2] += cnt;
        m[no / 2 - 1] += cnt;
      } else {
        m[no / 2] += 2 * cnt;
      }
    }
    cout << (cool) / 2 << " " << (cool - 1) / 2;
    cout << "\n";
  }
  return 0;
}
