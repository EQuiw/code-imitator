#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>

using namespace std;
map<long long, long long> mp;

priority_queue<long long> q;
int req[1111], num[55][55];
int tail[55];
int mincal(int cnt, int per) {
  int l, r;
  l = 0, r = 1000000;
  while (r - l > 1) {
    int mid = (l + r) >> 1;
    if (1.0 * per * mid * 1.1 + 1e-8 >= cnt)
      r = mid;
    else
      l = mid;
  }
  if (1.0 * per * r * 0.9 - 1e-8 >= cnt)
    return -1;
  return r;
}
int maxcal(int cnt, int per) {
  int l, r;
  l = 0, r = 1000001;
  while (r - l > 1) {
    int mid = (l + r) >> 1;
    if (1.0 * per * mid * 0.9 - 1e-8 <= cnt)
      l = mid;
    else
      r = mid;
  }
  if (1.0 * per * l * 1.1 + 1e-8 <= cnt)
    return -1;
  return l;
}
int main() {
  freopen("B-small-attempt1.in", "r", stdin);
  freopen("B-small-attempt1.out", "w", stdout);
  int tt, ri = 0;
  scanf("%d", &tt);
  while (tt--) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
      scanf("%d", &req[i]);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        scanf("%d", &num[i][j]);
      }
      sort(num[i], num[i] + m);
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      tail[i] = 0;
    }
    while (true) {
      int l, r;
      l = 0, r = 1000000;
      int minid = -1;
      int one, cnt;
      for (int i = 0; i < n; ++i) {
        if (minid == -1 ||
            (long long)cnt * req[i] > (long long)num[i][tail[i]] * one) {
          minid = i;
          cnt = num[i][tail[i]];
          one = req[i];
        }
        int nowl, nowr;
        nowl = mincal(num[i][tail[i]], req[i]);
        nowr = maxcal(num[i][tail[i]], req[i]);
        l = max(l, nowl);
        r = min(r, nowr);
      }
      if (l <= r && r != 0) {
        ans++;
        for (int i = 0; i < n; ++i)
          tail[i]++;
      } else {
        tail[minid]++;
      }
      int flag = 1;
      for (int i = 0; i < n; ++i) {
        if (tail[i] == m)
          flag = 0;
      }
      if (flag == 0)
        break;
    }
    printf("Case #%d: %d\n", ++ri, ans);
  }
}
