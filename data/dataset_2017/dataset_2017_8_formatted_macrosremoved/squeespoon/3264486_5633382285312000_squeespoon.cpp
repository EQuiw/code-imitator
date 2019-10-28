#include <bits/stdc++.h>

using namespace std;

char s[32];
int num[32];
int ans[32];
int Min[32];

int len = 0;

bool dfs(int pos, int Min, bool Any) {
  if (pos == len)
    return 1;

  if (Any) {
    ans[pos] = 9;
    return dfs(pos + 1, Min, Any);
  } else {
    for (int i = num[pos]; i >= Min; i--) {
      if (dfs(pos + 1, i, i != num[pos])) {
        ans[pos] = i;
        return 1;
      }
    }

    return 0;
  }
}

int main() {
  freopen("B-small-attempt1.in", "r", stdin);
  freopen("B-small-attempt1.out", "w", stdout);
  int t;
  cin >> t;
  int cas = 0;
  while (t--) {
    cas++;

    scanf("%s", s);
    len = strlen(s);

    for (int i = 0; i < len; i++) {
      num[i] = s[i] - '0';
    }

    dfs(0, 0, 0);

    printf("Case #%d: ", cas);

    bool flag = 0;
    for (int i = 0; i < len; i++) {
      if (ans[i]) {
        flag = 1;
      }

      if (!flag && !ans[i])
        continue;

      cout << ans[i];
    }
    cout << endl;
  }

  return 0;
}
