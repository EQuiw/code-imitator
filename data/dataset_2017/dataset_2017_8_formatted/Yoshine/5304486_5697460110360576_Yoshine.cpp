#include <bits/stdc++.h>

using namespace std;

int r[1234], q[1234][1234], n, p, ans;
vector<int> v;

#define pb push_back
void work(int ca) {
  scanf("%d %d", &n, &p);
  ans = 0;
  v.clear();
  for (int i = 1; i <= p; i++)
    v.pb(i);
  for (int i = 1; i <= n; i++)
    scanf("%d", &r[i]);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= p; j++)
      scanf("%d", &q[i][j]);
  }
  int c, _1, _2;
  // for (int rr = 1;rr;rr = next_permutation(v.begin(),v.end())) {
  do {
    c = 0;
    for (int i = 0; i < v.size(); i++) {
      int xx = q[1][v[i]], yy = q[2][i + 1];
      _1 = xx * 10 / r[1] / 9;
      _2 = ceil(xx * 10 / r[1] / 11);
      bool ok = 0;
      for (int _ = _2; _ <= _1 && !ok; _++) {
        if (9 * _ * r[1] <= 10 * xx && 10 * xx <= 11 * _ * r[1])
          if (n == 1 || 9 * _ * r[2] <= 10 * yy && 10 * yy <= 11 * _ * r[2])
            ok = 1;
      }
      if (ok)
        c++;
    }
    ans = max(ans, c);
  } while (next_permutation(v.begin(), v.end()));
  printf("Case #%d: %d\n", ca, ans);
}

int main() {
  int tt;
  scanf("%d", &tt);
  for (int __ = 1; __ <= tt; __++)
    work(__);
  return 0;
}
