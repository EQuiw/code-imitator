#include <algorithm>
#include <assert.h>
#include <functional>
#include <iostream>
#include <map>
#include <math.h>
#include <memory.h>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> Pi;

#define Fi first
#define Se second
#define pb(x) push_back(x)
#define sz(x) (int)x.size()
#define rep(i, n) for (int i = 0; i < n; i++)
#define repp(i, n) for (int i = 1; i <= n; i++)
#define all(x) x.begin(), x.end()

#define ABS(x) (((x) > 0) ? (x) : (-(x)))
#define MAX2(x, y) (((x) > (y)) ? (x) : (y))
#define MIN2(x, y) (((x) < (y)) ? (x) : (y))

#define MAX3(x, y, z)                                                          \
  ((x) > (y) ? ((x) > (z) ? (x) : (z)) : ((y) > (z) ? (y) : (z)))
#define MIN3(x, y, z)                                                          \
  ((x) < (y) ? ((x) < (z) ? (x) : (z)) : ((y) < (z) ? (y) : (z)))
#define MID3(val1, val2, val3)                                                 \
  MAX2(MIN2(MAX2(val1, val2), val3), MIN2(val1, val2))

#define geti1(X) scanf("%d", &X)
#define geti2(X, Y) scanf("%d%d", &X, &Y)
#define geti3(X, Y, Z) scanf("%d%d%d", &X, &Y, &Z)
#define geti4(X, Y, Z, W) scanf("%d%d%d%d", &X, &Y, &Z, &W)

#define GET_MACRO(_1, _2, _3, _4, NAME, ...) NAME
#define geti(...)                                                              \
  GET_MACRO(__VA_ARGS__, geti4, geti3, geti2, geti1)(__VA_ARGS__)

#define INF 987654321
#define IINF 987654321987654321

int N, M, T, K, tc;

void solve() {
  ll n, k;
  cin >> n >> k;
  ll a, b, ac, bc; // a > b,
  a = n;
  ac = 1;
  b = 0;
  bc = 0;
  bool hasb = false;
  ll cur = 0;
  while (true) {

    if (hasb && a < b) {
      swap(a, b);
      swap(ac, bc);
    }
    // printf("%lld %lld [%d] %lld %lld\n",a,ac,hasb, b,bc);
    if (cur + ac >= k) {
      if (a % 2 == 0) {
        printf("%lld %lld\n", a / 2, a / 2 - 1);
        return;
      } else {
        printf("%lld %lld\n", a / 2, a / 2);
        return;
      }
    }
    if (hasb && cur + ac + bc >= k) {
      if (b % 2 == 0) {
        printf("%lld %lld\n", b / 2, b / 2 - 1);
        return;
      } else {
        printf("%lld %lld\n", b / 2, b / 2);
        return;
      }
    }

    ll na, nb, nac, nbc;
    nac = nbc = 0;
    map<ll, ll> mp;
    if (a % 2 == 0) {
      mp[a / 2] += ac;
      mp[a / 2 - 1] += ac;
    } else {
      mp[a / 2] += ac;
      mp[a / 2] += ac;
    }
    if (hasb) {
      if (b % 2 == 0) {
        mp[b / 2] += bc;
        mp[b / 2 - 1] += bc;
      } else {
        mp[b / 2] += bc;
        mp[b / 2] += bc;
      }
    }
    int cnt = 0;
    for (auto e : mp) {
      if (cnt == 0) {
        na = e.Fi;
        nac = e.Se;
        cnt++;
      } else {
        nb = e.Fi;
        nbc = e.Se;
        cnt++;
      }
    }
    if (cnt == 1)
      hasb = false;
    if (cnt == 2)
      hasb = true;
    if (cnt >= 3)
      printf("!!!");

    cur += ac;
    if (hasb)
      cur += bc;

    a = na;
    b = nb;
    ac = nac;
    bc = nbc;
  }
}

int main(void) {
  freopen("output.txt", "w", stdout);
  geti(tc);
  for (int tcx = 1; tcx <= tc; tcx++) {
    printf("Case #%d: ", tcx);
    solve();
  }
}
