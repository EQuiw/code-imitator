#include <bits/stdc++.h>
using namespace std;
char s[330];
int T;
int n;
int a[111];
void solve() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  for (int i = 1; i <= n; i++)
    a[i] = s[i] - '0';

  for (int i = 1; i <= n; i++) {
    int x = a[i];
    int ok = 1;
    for (int j = i + 1; j <= n; j++) {
      if (x > a[j]) {
        ok = 0;
        break;
      }
      if (x < a[j])
        break;
    }
    if (!ok) {
      a[i]--;
      for (int j = i + 1; j <= n; j++)
        a[j] = 9;
      break;
    }
  }

  int l = 1;
  while (a[l] == 0)
    l++;
  for (int i = l; i <= n; i++)
    putchar(a[i] + '0');
  puts("");
}
int main() {
  cin >> T;
  for (int t = 1; t <= T; t++) {
    printf("Case #%d: ", t);
    solve();
  }
  return 0;
}
