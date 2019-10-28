#include <cstdio>
#include <cstring>

const int MAXN = 100;

int n;
int a[MAXN];

long long max(long long x, long long y) { return x > y ? x : y; }

void init() {
  char tmp[50];
  scanf("%s", tmp);
  n = strlen(tmp);
  memset(a, 0, sizeof(a));
  for (int i = 0; i < n; ++i)
    a[n - i] = tmp[i] - '0';
}

void sub(int k) {
  if (a[k] > 0)
    --a[k];
  else {
    a[k] == 9;
    sub(k + 1);
  }
}

void solve() {
  int k = -1;
  while (k != 0) {
    k = 0;
    for (int i = n; i > 0; --i)
      if (a[i] < a[i + 1]) {
        k = i + 1;
        break;
      }
    if (k == 0)
      break;
    sub(k);
    for (int i = k - 1; i > 0; --i)
      a[i] = 9;
    while (n > 1 && a[n] == 0)
      --n;
  }
  for (int i = n; i > 0; --i)
    printf("%d", a[i]);
  printf("\n");
}

int main() {
  // freopen("b.in", "r", stdin);
  int tt;
  scanf("%d", &tt);
  for (int ii = 1; ii <= tt; ++ii) {
    init();
    printf("Case #%d: ", ii);
    solve();
  }
  return 0;
}
