#include <algorithm>
#include <cstring>
#include <ctype.h>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<bool> vb;
typedef std::vector<string> vs;
typedef std::vector<double> vd;
typedef std::vector<long long> vll;
typedef std::vector<std::vector<int>> vvi;
typedef vector<vvi> vvvi;
typedef vector<vll> vvll;
typedef std::vector<std::pair<int, int>> vpi;
typedef vector<vpi> vvpi;
typedef std::pair<int, int> pi;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;

const long long mod = 1000000007;

#define all(c) (c).begin(), (c).end()
#define sz(c) (int)(c).size()
#define forn(i, a, b) for (int i = a; i < b; i++)

#define pb push_back
#define mp make_pair
vll a;

int test1(ll nd) {
  ll dev = nd % a[0];
  if (dev == 0)
    return 1;
  else {
    if (11 * (nd - dev) >= 10 * nd)
      return 1;
    if (10 * nd >= 9 * (nd - dev + a[0]))
      return 1;
    return 0;
  }
}
int test2(ll nda, ll ndb) {
  //    vll t;
  //    ll da = nda % a[0];
  //    t.pb((nda-da)/a[0]);
  //    t.pb((nda-da)/a[0]+1);
  //    ll db = ndb % a[1];
  //    t.pb((ndb-db)/a[1]);
  //    t.pb((ndb-db)/a[1]+1);
  //    for(auto x : t) {
  //        ll ca = x*a[0];
  //        ll cb = x*a[1];
  //        if(nda*10 <= ca*11 && nda*10 >= ca*9 && ndb*10 <= cb*11 && ndb*10 >=
  //        cb*9) return 1;
  //    }
  ll mx = min((10 * nda) / (9 * a[0]), (10 * ndb) / (9 * a[1]));
  ll mn = max((10 * nda + 11 * a[0] - 1) / (11 * a[0]),
              (10 * ndb + 11 * a[1] - 1) / (11 * a[1]));
  if (mx >= mn)
    return 1;
  return 0;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "rt", stdin);
  freopen("output.txt", "wt", stdout);
#endif
  int affu;
  scanf("%d", &affu);
  forn(rruq, 0, affu) {
    printf("Case #%d: ", rruq + 1);
    int n, p;
    scanf("%d %d", &n, &p);
    a.resize(n);
    vvll s(n, vll(p, 0));
    forn(i, 0, n) scanf("%lld", &a[i]);
    forn(i, 0, n) forn(j, 0, p) scanf("%lld", &s[i][j]);
    vi fac;
    forn(i, 0, p) fac.pb(i);
    int ans = 0;
    if (n == 1) {
      forn(i, 0, p) {
        //                cout<<s[0][i] << "aag" << test1(s[0][i])<<"   ";
        ans += test1(s[0][i]);
      }
    } else {
      do {
        int cur = 0;
        forn(i, 0, p) { cur += test2(s[0][i], s[1][fac[i]]); }
        ans = max(ans, cur);

      } while (std::next_permutation(all(fac)));
    }
    printf("%d\n", ans);
  }
}
