#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
typedef long long ll;
typedef pair<int, int> pt;
const int base = 1000000007;
const int maxn = 1000002;

int n, res, K;
bool a[maxn], b[maxn];
char s[maxn];

void solve(int test) {
  int i, j, k, u, v;
  bool kt = 0, found;

  scanf("%s", s + 1);
  n = strlen(s + 1);
  scanf("%d\n", &K);
  for (i = 1; i <= n; i++) {
    if (s[i] == '+')
      b[i] = 1;
    else
      b[i] = 0;
    a[i] = 0;
  }

  kt = 0;
  found = true;
  res = 0;
  for (i = 1; i <= n; i++) {
    kt ^= a[i];
    b[i] ^= kt;
    if (b[i] == 0) {
      if (i <= n - K + 1) {
        kt ^= 1;
        res++;
        a[i + K] ^= 1;
      } else
        found = false;
    }
  }

  printf("Case #%d: ", test);
  if (found)
    printf("%d\n", res);
  else
    printf("IMPOSSIBLE\n");
}

int main() {
  int i, t;
  freopen("cja.in", "r", stdin);
  freopen("output.out", "w", stdout);

  scanf("%d", &t);
  for (i = 1; i <= t; i++)
    solve(i);

  return 0;
}
