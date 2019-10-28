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

#define pb push_back
#define mp make_pair
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define ren(i, a, b) for (int i = a; i >= b; i--)
#define ff first
#define ss second
#define pll pair<long long int, long long int>
#define pii pair<int, int>
#define vll vector<long long int>
#define vii vector<int>
#define gi(n) scanf("%d", &n)
#define gll(n) scanf("%lld", &n)
#define gstr(n) scanf("%s", n)
#define gl(n) cin >> n
#define oi(n) printf("%d", n)
#define oll(n) printf("%lld", n)
#define ostr(n) printf("%s", n)
#define ol(n) cout << n
#define os cout << " "
#define on cout << "\n"
#define o2(a, b) cout << a << " " << b
#define all(n) n.begin(), n.end()
#define present(s, x) (s.find(x) != s.end())
#define cpresent(s, x) (find(all(s), x) != s.end())
#define tr(container, it)                                                      \
  for (__typeof(container.begin()) it = container.begin();                     \
       it != container.end(); it++)
using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<vector<ll>> mat;

int main() {
  ios_base::sync_with_stdio(false);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t, t1 = 0;
  gl(t);
  vll v;
  ll x = 1;
  rep(i, 1, 19) {
    v.pb(x);
    x = x * 10 + 1;
  }
  while (t--) {
    t1++;
    ol("Case #");
    ol(t1);
    ol(": ");

    ll n;
    cin >> n;
    ll ans = 0;
    rep(i, 1, 9) {
      int sz = v.size();
      ren(j, sz - 1, 0) {
        if (v[j] <= n) {
          n -= v[j];
          ans += v[j];
          break;
        }
      }
    }
    ol(ans);
    on;
  }
  return 0;
}
