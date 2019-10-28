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
        na = e.first;
        nac = e.second;
        cnt++;
      } else {
        nb = e.first;
        nbc = e.second;
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
  scanf("%d", &tc);
  for (int tcx = 1; tcx <= tc; tcx++) {
    printf("Case #%d: ", tcx);
    solve();
  }
}
