// Written by Li Bo
#include <bits/stdc++.h>
using namespace std;
const int N = 1200;
bitset<N> l, p;
int n, k;
char s[N];

int main() {
  int T;
  scanf("%d", &T);
  int cas = 0;
  while (T--) {
    scanf("%s %d", s, &k);
    n = strlen(s);
    p.reset();
    l.reset();

    for (int i = 0; i < n; i++)
      l[i] = s[i] == '-';

    for (int i = 0; i < k; i++)
      p[i] = 1;

    int time = 0;
    for (int i = 0; i + k <= n; i++) {
      if (l.test(i)) {
        l ^= p;
        time++;
      }
      p <<= 1;
    }

    if (l.count())
      printf("Case #%d: IMPOSSIBLE\n", ++cas);
    else
      printf("Case #%d: %d\n", ++cas, time);
  }
  return 0;
}
