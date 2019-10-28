#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:100000000000")
#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
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
#include <utility>
#include <vector>

using namespace std;
#define FR(i, n) for (int(i) = 0; (i) < (n); (i)++)
#define FOR(i, c, n) for (int(i) = (c); (i) < (n); (i)++)
#define REP(it, v, cont)                                                       \
  for (cont::iterator(it) = (v).begin(); (it) != (v).end(); ++(it))
#define CLR(a, c) memset((a), (c), sizeof(a))
#define ALL(v) (v).begin(), (v).end()
#define SQR(a) ((a) * (a))
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;

PLL divideme(ll n) {
  n--;
  ll k1 = n / 2;
  ll k2 = n - k1;
  return PLL(min(k1, k2), max(k1, k2));
}
bool comp(const pair<PLL, ll> &a, const pair<PLL, ll> &b) {
  return (a.first.first < b.first.first ||
          a.first.first == b.first.first && a.first.second > b.first.second);
}

int main() {
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
  int Tcas;
  cin >> Tcas;
  FR(cas, Tcas) {
    printf("Case #%d: ", cas + 1);
    ll n, k;
    cin >> n >> k;
    ll two = 1;
    map<PLL, ll> mp;
    mp[divideme(n)] = 1;
    vector<pair<PLL, ll>> res;
    ll freeSlot = 1;
    while (freeSlot < k) {
      two <<= 1;
      freeSlot += two;
      map<PLL, ll> temp;
      for (map<PLL, ll>::iterator it = mp.begin(); it != mp.end(); ++it) {
        PLL p1 = divideme(it->first.first);
        PLL p2 = divideme(it->first.second);
        if (temp.find(p1) == temp.end())
          temp[p1] = 0;
        if (temp.find(p2) == temp.end())
          temp[p2] = 0;
        temp[p1] += it->second;
        temp[p2] += it->second;
      }
      mp = temp;
      if (freeSlot >= k) {
        k = k - (freeSlot - two);
        break;
      }
    }
    for (map<PLL, ll>::iterator it = mp.begin(); it != mp.end(); ++it)
      res.push_back(*it);
    sort(ALL(res));
    reverse(ALL(res));
    FR(i, res.size()) {
      if (k <= res[i].second) {
        cout << res[i].first.second << " " << res[i].first.first << endl;
        break;
      } else
        k -= res[i].second;
    }
  }
}
