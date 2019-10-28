#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
#define CLR(a, x) memset(a, x, sizeof(a))
using namespace std;
const int maxn = 410;
const int maxm = 20010;
const int INF = 0x3f3f3f3f;
template <typename T> inline void read(T &x) {
  x = 0;
  bool f = false;
  char ch = getchar();
  while (ch < '0' || '9' < ch) {
    if (ch == '-')
      f = !f;
    ch = getchar();
  }
  while ('0' <= ch && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  if (f)
    x = -x;
}
const int N = 60;
struct node {
  int x, y;
  node() {}
  node(int _x, int _y) {
    x = _x;
    y = _y;
  }
  bool operator<(const node &t) const {
    return (x == t.x) ? (y < t.y) : (x < t.x);
  }
  void output() { cout << "(" << x << "," << y << ")\t"; }
} pack[N][N];
int n, p, a[N], value[N][N], ans;
int pos[N];
void input() {
  read(n);
  read(p);
  for (int i = 1; i <= n; i++)
    read(a[i]);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= p; j++)
      read(value[i][j]);
}
void pre() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= p; j++) {
      int tmpx = floor(1.0 * value[i][j] / 0.9 / a[i]);
      int tmpy = ceil(1.0 * value[i][j] / 1.1 / a[i]);
      //            cout<<value[i][j]<<" "<<a[i]<<"   "<<tmpx<<" "<<tmpy<<endl;
      if (tmpy <= tmpx)
        pack[i][j] = node(tmpy, tmpx);
      else
        pack[i][j] = node(-1, -1);
    }
    sort(pack[i] + 1, pack[i] + 1 + p);
  }
  //    for (int i=1;i<=n;i++)
  //    {
  //        for (int j=1;j<=p;j++) pack[i][j].output();
  //        cout<<endl;
  //    }
}
void work() {
  for (int i = 1; i <= n; i++)
    pos[i] = 1;
  int nowk = 1;
  bool flag = true;
  while (flag) {
    for (int i = 1; i <= n; i++) {
      int q = pos[i];
      while (q <= p && pack[i][q].y < nowk)
        q++;
      pos[i] = q;
      if (q > p) {
        flag = false;
        break;
      }
    }
    if (!flag)
      break;
    bool f = true;
    for (int i = 1; i <= n; i++) {
      if (pack[i][pos[i]].x <= nowk && pack[i][pos[i]].y >= nowk)
        continue;
      else
        f = false;
      break;
    }
    if (f) {
      ans++;
      for (int i = 1; i <= n; i++)
        pos[i]++;
    } else
      nowk++;
  }
}
int main() {
#ifdef VGel
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-small-attempt0.out", "w", stdout);
#endif // VGel
  int T_T;
  scanf("%d", &T_T);
  for (int T = 1; T <= T_T; T++) {
    input();
    pre();
    ans = 0;
    work();
    printf("Case #%d: %d\n", T, ans);
  }
}
