#include <bits/stdc++.h>

using namespace std;

const int N = 77;

char s[N];

bool check(long long k) {
  long long pw = 1;
  for (int i = 0; s[i]; ++i) {
    if (s[i] == 'S') {
      k -= pw;
    } else {
      pw *= 2;
    }
  }
  return k >= 0;
}

bool work() {
  for (int i = (int)strlen(s) - 1; i >= 1; --i) {
    if (s[i] == 'S' && s[i - 1] == 'C') {
      swap(s[i], s[i - 1]);
      return true;
    }
  }
  return false;
}

int main() {
  int tt;
  scanf("%d", &tt);
  for (int cc = 1; cc <= tt; ++cc) {
    printf("Case #%d: ", cc);
    int k;
    scanf("%d %s", &k, s);
    int ans = 0;
    while (!check(k)) {
      if (!work()) {
        ans = -1;
        break;
      }
      ++ans;
    }
    if (ans == -1) {
      puts("IMPOSSIBLE");
    } else {
      printf("%d\n", ans);
    }
  }
}
