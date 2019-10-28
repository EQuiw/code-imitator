#include <algorithm>
#include <assert.h>
#include <deque>
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
#include <unordered_map>
#include <vector>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> Pi;
typedef pair<ll, ll> Pll;
int N, M, K, tc;
ll r[150];
ll p[150][150];
set<Pll> cur[150];
Pll range[150][150];
struct event {
  ll n;
  ll x;
  ll y;
  ll t;
};

bool cmp(event e1, event e2) {
  if (e1.n == e2.n)
    return e1.t > e2.t;
  return e1.n < e2.n;
}
ll gcd(ll a, ll b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
struct fraction {
  ll x, y;
  fraction() {
    x = 0;
    y = 1;
  }
  fraction(ll _x, ll _y) {
    x = _x;
    y = _y;
    ll g = gcd(x, y);
    x = x / g;
    y = y / g;
  }

  ll ceil() { return (x + y - 1) / y; }
  ll floor() { return x / y; }
  void print() { printf("%lld/%lld", x, y); }
  fraction operator*(fraction a) {
    fraction res = fraction(a.x * x, a.y * y);
    return res;
  }
};

void solve2() {
  for (int i = 0; i < 150; i++)
    for (int j = 0; j < 150; j++)
      range[i][j] = {-1, -1};
  for (int i = 0; i < 150; i++)
    cur[i].clear();
  memset(p, 0, sizeof p);
  memset(r, 0, sizeof r);
  scanf("%d%d", &N, &M);
  for (int i = 1; i <= N; i++)
    scanf("%lld", r + i);
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++)
      scanf("%lld", &p[i][j]);
  }

  ll ans = 0;

  vector<int> v;
  for (int i = 1; i <= M; i++)
    v.push_back(i);

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      fraction nl, nr;
      nl = fraction(p[i][j], r[i]);
      nl = nl * fraction(10, 11);
      nr = fraction(p[i][j], r[i]);
      nr = nr * fraction(10, 9);

      ll nleft = nl.ceil();
      ll nright = nr.floor();
      if (nleft > nright)
        continue;
      range[i][j] = {nleft, nright};
      event t1, t2;
      // 1 이면 들어오고 -1이면 나감
      // printf("[%lld,%lld]\n",nleft,nright);
    }
  }

  if (N == 1) {
    for (int j = 1; j <= M; j++) {
      if (range[1][j].first != -1 && range[1][j].second != -1)
        ans++;
    }
    printf("%lld\n", ans);
    return;
  }

  do {
    ll cnt = 0;
    for (int j = 1; j <= M; j++) {
      int jj = v[j - 1];
      if (range[1][j].first == -1 || range[1][j].second == -1)
        continue;
      if (range[2][jj].first == -1 || range[2][jj].second == -1)
        continue;
      ll curl = range[1][j].first;
      ll curr = range[1][j].second;
      curl = max(curl, range[2][jj].first);
      curr = min(curr, range[2][jj].second);
      if (curl <= curr)
        cnt++;
    }
    ans = max(cnt, ans);
  } while (next_permutation(v.begin(), v.end()));

  printf("%lld\n", ans);
}
void solve() {
  for (int i = 0; i < 150; i++)
    cur[i].clear();
  memset(p, 0, sizeof p);
  memset(r, 0, sizeof r);
  scanf("%d%d", &N, &M);
  for (int i = 1; i <= N; i++)
    scanf("%lld", r + i);
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++)
      scanf("%lld", &p[i][j]);
  }

  ll ans = 0;
  vector<event> v;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      fraction nl, nr;
      nl = fraction(p[i][j], r[i]);
      nl = nl * fraction(10, 11);
      nr = fraction(p[i][j], r[i]);
      nr = nr * fraction(10, 9);
      // nl = ((long double)1.0*p[i][j])/(1.0*r[i]); nl *= (10.0/11.0);
      // nr = ((long double)1.0*p[i][j])/(1.0*r[i]); nr *= (10.0/9.0);
      // cout << nl << " " << nr << endl;
      ll nleft = nl.ceil();
      ll nright = nr.floor();
      if (nleft > nright)
        continue;
      // range[i][j] = {nleft,nright};
      event t1, t2;
      // 1 이면 들어오고 -1이면 나감
      t1.n = nleft;
      t1.y = i;
      t1.x = j;
      t1.t = 1;
      t2.n = nright;
      t2.y = i;
      t2.x = j;
      t2.t = -1;
      // printf("[%lld,%lld]\n",nleft,nright);
      v.push_back(t1);
      v.push_back(t2);
    }
    // printf("\n");
  }
  sort(v.begin(), v.end(), cmp);

  for (auto e : v) {
    if (e.t == 1) {
      cur[e.y].insert({e.n, e.x});
    }
    bool ok = true;
    for (int i = 1; i <= N; i++) {
      if (cur[i].size() == 0)
        ok = false;
    }
    if (ok) {
      ans++;
      for (int i = 1; i <= N; i++) {
        Pll die = *(cur[i].begin());
        //	printf("%lld ",p[i][die.Se]);
        cur[i].erase(die);
      }
      // printf("\n");
    }
    if (e.t == -1) {
      if (cur[e.y].find({e.n, e.x}) != cur[e.y].end())
        cur[e.y].erase({e.n, e.x});
    }
  }

  printf("%lld\n", ans);
}

int main(void) {
  freopen("output2.txt", "w", stdout);
  scanf("%d", &tc);
  for (int t = 1; t <= tc; t++) {
    printf("Case #%d: ", t);
    solve2();
  }
}
