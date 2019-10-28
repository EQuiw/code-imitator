#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> P;
const LL inf = 1LL << 61;
const LL mod = 1000000007;
const int maxn = 1010;

int main() {
  // std::ios::sync_with_stdio(false);
  int i = 0, j = 0, k = 0, kase = 0;
  int n, t;
  char str[maxn];
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("out.txt", "w", stdout);
  scanf("%d", &t);
  while (t--) {
    scanf("%s%d", str, &k);
    int len = strlen(str), ans = 0;
    for (i = 0; i <= len - k; i++) {
      if (str[i] == '+')
        continue;
      ans++;
      for (j = i; j < i + k; j++) {
        if (str[j] == '-')
          str[j] = '+';
        else
          str[j] = '-';
      }
    }
    bool flag = false;
    for (j = i; j < len; j++) {
      if (str[j] == '-') {
        flag = true;
        break;
      }
    }
    if (flag) {
      printf("Case #%d: IMPOSSIBLE\n", ++kase);
    } else {
      printf("Case #%d: %d\n", ++kase, ans);
    }
  }

  return 0;
}
