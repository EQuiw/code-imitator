#include <algorithm>
#include <cstdio>
using namespace std;

int Case, n, r, o, y, g, b, v;
char s[1000 + 5], t[1000 + 5];

void Brute() {
  int sum = r + b;
  if (y > sum) {
    puts("IMPOSSIBLE");
    return;
  }
  for (int i = 0, op = (r >= b ? 1 : 0); i < sum; i++) {
    if (!b || ((i + op & 1) && r > 0))
      r--, s[i] = 'R';
    else
      b--, s[i] = 'B';
  }
  int len = 0;
  for (int i = 0; i < sum - y; i++)
    t[len++] = s[i];
  for (int i = sum - y; i < sum; i++)
    t[len++] = s[i], t[len++] = 'Y';
  t[len] = '\0';
  bool ok = 1;
  for (int i = 0; ok && i < len - 1; i++)
    ok = t[i] != t[i + 1];
  if (!ok)
    puts("IMPOSSIBLE");
  else
    printf("%s\n", t);
}

void Solve() { puts(""); }

int main() {
  scanf("%d", &Case);
  for (int T = 1; T <= Case; T++) {
    scanf("%d", &n);
    scanf("%d%d%d%d%d%d", &r, &o, &y, &g, &b, &v);
    printf("Case #%d: ", T);
    if (o == 0 && g == 0 && v == 0)
      Brute();
    else
      Solve();
  }
  return 0;
}
