#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;
typedef long long ll;
const pair<ll, ll> getValue(pair<ll, ll> &x) {
  if (x.first <= 0 || x.second <= 0)
    return make_pair(0, 0);
  if (x.first & 1)
    return make_pair(x.first >> 1, x.first >> 1);
  else
    return make_pair((x.first >> 1) - 1, x.first >> 1);
}
const bool cmp(pair<ll, ll> &v1, pair<ll, ll> &v2) {
  if (min(v1.first, v1.second) != min(v2.first, v2.second))
    return min(v1.first, v1.second) > min(v2.first, v2.second);
  if (max(v1.first, v1.second) != max(v2.first, v2.second))
    return max(v1.first, v1.second) > max(v2.first, v2.second);
  return 1;
}
void split(pair<ll, ll> &fa, pair<ll, ll> &ch1, pair<ll, ll> &ch2) {
  if (!fa.second || !fa.first) {
    ch1 = ch2 = make_pair(0, 0);
    return;
  }
  if (fa.first & 1)
    ch1 = ch2 = make_pair(fa.first >> 1, fa.second);
  else {
    ch1 = make_pair((fa.first >> 1) - 1, fa.second);
    ch2 = make_pair(fa.first >> 1, fa.second);
  }
}
void print(pair<ll, ll> x) { printf("print (%lld %lld)\n", x.first, x.second); }
void mergeTwo(pair<ll, ll> &x, pair<ll, ll> &y) {
  if (x.first == y.first) {
    x.second += y.second;
    y.second = 0;
  }
}
void merge(pair<ll, ll> &x1, pair<ll, ll> &x2, pair<ll, ll> &y1,
           pair<ll, ll> &y2, pair<ll, ll> &y3, pair<ll, ll> &y4) {

  mergeTwo(y1, y2);
  mergeTwo(y1, y3);
  mergeTwo(y1, y4);
  mergeTwo(y2, y3);
  mergeTwo(y2, y4);
  mergeTwo(y3, y4);
  /*print(y1);
  print(y2);
  print(y3);
  print(y4);*/
  if (!y1.first || !y1.second) {
    if (y3.first && y3.second)
      swap(y1, y3);
    if (y4.first && y4.second)
      swap(y1, y4);
  }
  if (!y2.first || !y2.second) {
    if (y3.first && y3.second)
      swap(y2, y3);
    if (y4.first && y4.second)
      swap(y2, y4);
  }
  x1 = y1;
  x2 = y2;
}
int main() {
  // freopen("in.txt","r",stdin);
  // freopen("out2.txt","w",stdout);
  int T;
  cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    ll n, m;
    pair<ll, ll> ans, now1, now2, next1, next2, next3 = make_pair(-1, -1),
                                                next4 = make_pair(-1, -1);
    cin >> n >> m;
    now1 = make_pair(n, 1);
    now2 = make_pair(0, 0);
    ans = getValue(now1);
    ll cnt = 1;
    while (m) {
      pair<ll, ll> v1 = getValue(now1), v2 = getValue(now2);
      // printf("m = %lld\n", m);
      //	printf("now = %lld %lld %lld %lld\n", now1.first, now1.second,
      // now2.first, now2.second); 	printf("v = %lld %lld %lld %lld \n",
      // v1.first, v1.second , v2.first, v2.second);
      bool flag = cmp(v1, v2);
      // printf("flag = %d\n", flag);
      // system("pause");
      if (flag) {
        if (m > now1.second)
          m -= now1.second;
        else {
          ans = v1;
          break;
        }
        split(now1, next1, next2);
        if (m > now2.second)
          m -= now2.second;
        else {
          ans = v2;
          break;
        }
        split(now2, next3, next4);
      } else {
        if (m > now2.second)
          m -= now2.second;
        else {
          ans = v2;
          break;
        }
        split(now2, next3, next4);
        if (m > now1.second)
          m -= now1.second;
        else {
          ans = v1;
          break;
        }
        split(now1, next1, next2);
      }
      if (now1.first & 1) {
        next1.first = now1.first >> 1;
        next1.second = 2 * now1.second + now2.second;
        next2.first = next1.first + 1;
        next2.second = now2.second;
      } else {
        next1.first = (now1.first >> 1) - 1;
        next1.second = now1.second;
        next2.first = next1.first + 1;
        next2.second = now1.second + 2 * now2.second;
      }
      now1 = next1;
      now2 = next2;
      // merge(now1, now2, next1, next2, next3, next4);
    }
    printf("Case #%d: ", cas);
    cout << max(ans.first, ans.second) << " " << min(ans.first, ans.second)
         << '\n';
  }
  return 0;
}
