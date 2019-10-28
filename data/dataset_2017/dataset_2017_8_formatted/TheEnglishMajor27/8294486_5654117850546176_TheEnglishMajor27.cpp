#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
typedef long long ll;
typedef pair<int, int> pt;
const int base = 1000000007;
const int maxn = 100002;

int n;
char res[maxn];
pt a[maxn];

bool cmp(pt a, pt b) { return (a.x > b.x); }

void solve(int test) {
  int i, j;
  int s[10];

  scanf("%d", &n);
  for (i = 1; i <= 6; i++)
    scanf("%d", &s[i]);
  a[1].x = s[1];
  a[1].y = 'R';
  a[2].x = s[3];
  a[2].y = 'Y';
  a[3].x = s[5];
  a[3].y = 'B';
  // if (n<=20) printf("%d %d 0 %d 0 %d 0 \n",n,a[1].x,a[2].x,a[3].x);

  printf("Case #%d: ", test);
  if (a[1].x > a[2].x + a[3].x) {
    printf("IMPOSSIBLE\n");
    return;
  }
  if (a[2].x > a[1].x + a[3].x) {
    printf("IMPOSSIBLE\n");
    return;
  }
  if (a[3].x > a[2].x + a[1].x) {
    printf("IMPOSSIBLE\n");
    return;
  }

  sort(a + 1, a + 3 + 1, cmp);
  res[1] = a[1].y;
  a[1].x--;
  for (i = 2; i <= n; i++) {
    sort(a + 1, a + 3 + 1, cmp);
    if (a[1].y != res[i - 1]) {
      res[i] = a[1].y;
      a[1].x--;
    } else {
      if (res[i - 2] == a[2].y) {
        if (a[2].x > 0) {
          a[2].x--;
          res[i] = a[2].y;
        } else {
          a[3].x--;
          res[i] = a[3].y;
        }
      } else if (res[i - 2] == a[3].y) {
        if (a[3].x > 0) {
          a[3].x--;
          res[i] = a[3].y;
        } else {
          a[2].x--;
          res[i] = a[2].y;
        }
      } else if (a[2].x > 0) {
        a[2].x--;
        res[i] = a[2].y;
      } else if (a[3].x > 0) {
        a[3].x--;
        res[i] = a[3].y;
      }
    }
  }
  if (res[n] == res[1])
    swap(res[n], res[n - 1]);
  res[n + 1] = 0;

  printf("%s\n", res + 1);
}

int main() {
  int i, t;
  freopen("B.in", "r", stdin);
  freopen("B1.out", "w", stdout);

  scanf("%d", &t);
  for (i = 1; i <= t; i++)
    solve(i);

  return 0;
}
