
#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;

using namespace std;

pair<ll, ll> solve_small(ll n, ll k) {
  priority_queue<ll> Q;
  Q.push(n);
  for (ll i = 0; i < k - 1; i++) {
    ll x = Q.top();
    Q.pop();
    Q.push((x - 1) / 2);
    Q.push(x / 2);
  }
  ll x = Q.top();
  return make_pair(x / 2, (x - 1) / 2);
}

int main() {
  int T;
  cin >> T;
  for (int cs = 1; cs <= T; cs++) {
    ll n, k;
    cin >> n >> k;
    auto ans = solve_small(n, k);
    printf("Case #%d: %lld %lld\n", cs, ans.first, ans.second);
  }

  return 0;
}
