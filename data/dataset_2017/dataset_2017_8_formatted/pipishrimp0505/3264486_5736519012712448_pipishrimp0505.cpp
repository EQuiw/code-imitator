#include <bits/stdc++.h>

using namespace std;

char s[1100];
int a[1100];

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-small-attempt0.out", "w", stdout);
  int T;
  scanf("%d", &T);
  for (int Case = 1; Case <= T; Case++) {
    scanf("%s", s);
    int n = strlen(s);
    for (int i = 0; i < n; i++) {
      if (s[i] == '-')
        a[i] = 1;
      else
        a[i] = 0;
    }
    int k;
    scanf("%d", &k);
    int ans = 0;
    for (int i = 0; i < n - k; i++) {
      if (a[i]) {
        for (int j = i; j <= i + k - 1; j++)
          a[j] ^= 1;
        ans++;
      }
    }
    int tmp = 0;
    for (int i = n - k + 1; i < n; i++)
      if (a[i] != a[i - 1])
        tmp = 1;
    if (a[n - 1] == 1)
      ans++;
    if (tmp)
      printf("Case #%d: IMPOSSIBLE\n", Case);
    else
      printf("Case #%d: %d\n", Case, ans);
  }
}
