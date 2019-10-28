#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 5;

char mp[30][30];
char ans[30];
int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-small-attempt0.out", "w", stdout);
  int t, ca = 1;
  scanf("%d", &t);
  while (t--) {
    printf("Case #%d:\n", ca++);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        cin >> mp[i][j];
    memset(ans, 0, sizeof(ans));
    for (int i = 0; i < n; i++) {
      int j = 0;
      while (j < m && mp[i][j] == '?')
        j++;
      if (j < m) {
        for (int k = 0; k < j; k++)
          mp[i][k] = mp[i][j];
        for (int k = j + 1; k < m; k++)
          if (mp[i][k] == '?')
            mp[i][k] = mp[i][k - 1];
      } else
        ans[i] = 1;
    }
    int i = 0;
    while (ans[i])
      i++;
    for (int j = 0; j < i; j++)
      strcpy(mp[j], mp[i]);
    for (int j = i + 1; j < n; j++)
      if (ans[j])
        strcpy(mp[j], mp[j - 1]);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++)
        putchar(mp[i][j]);
      //            if(i!=n-1)
      puts("");
    }
  }
  return 0;
}
