#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pt;
const int base = 1000000007;
const int maxn = 100002;

int n;
char res[maxn];
pt a[maxn];

bool cmp(pt a, pt b) { return (a.first > b.first); }

void solve(int test) {
  int i, j;
  int s[10];

  scanf("%d", &n);
  for (i = 1; i <= 6; i++)
    scanf("%d", &s[i]);
  a[1].first = s[1];
  a[1].second = 'R';
  a[2].first = s[3];
  a[2].second = 'Y';
  a[3].first = s[5];
  a[3].second = 'B';
  // if (n<=20) printf("%d %d 0 %d 0 %d 0 \n",n,a[1].x,a[2].x,a[3].x);

  printf("Case #%d: ", test);
  if (a[1].first > a[2].first + a[3].first) {
    printf("IMPOSSIBLE\n");
    return;
  }
  if (a[2].first > a[1].first + a[3].first) {
    printf("IMPOSSIBLE\n");
    return;
  }
  if (a[3].first > a[2].first + a[1].first) {
    printf("IMPOSSIBLE\n");
    return;
  }

  sort(a + 1, a + 3 + 1, cmp);
  res[1] = a[1].second;
  a[1].first--;
  for (i = 2; i <= n; i++) {
    sort(a + 1, a + 3 + 1, cmp);
    if (a[1].second != res[i - 1]) {
      res[i] = a[1].second;
      a[1].first--;
    } else {
      if (res[i - 2] == a[2].second) {
        if (a[2].first > 0) {
          a[2].first--;
          res[i] = a[2].second;
        } else {
          a[3].first--;
          res[i] = a[3].second;
        }
      } else if (res[i - 2] == a[3].second) {
        if (a[3].first > 0) {
          a[3].first--;
          res[i] = a[3].second;
        } else {
          a[2].first--;
          res[i] = a[2].second;
        }
      } else if (a[2].first > 0) {
        a[2].first--;
        res[i] = a[2].second;
      } else if (a[3].first > 0) {
        a[3].first--;
        res[i] = a[3].second;
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
