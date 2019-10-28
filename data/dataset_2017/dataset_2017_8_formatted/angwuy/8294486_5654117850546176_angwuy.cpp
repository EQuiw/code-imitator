#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>

const int MAXN = 1100;
const int MAXC = 6;

// Red, Orange, Yellow, Green, Blue, Violet
const int LINKS[6][6] = {{0, 0, 1, 1, 1, 0},  // R
                         {0, 0, 0, 0, 1, 0},  // O
                         {1, 0, 0, 0, 1, 1},  // Y
                         {1, 0, 0, 0, 0, 0},  // G
                         {1, 1, 1, 0, 0, 0},  // B
                         {0, 0, 1, 0, 0, 0}}; // V

const char C[6] = {'R', 'O', 'Y', 'G', 'B', 'V'};
const int L[6] = {3, -1, 5, -1, 1, -1};

int n;
int a[MAXC], b[MAXC];
int d[MAXC];

void init() {
  scanf("%d", &n);
  for (int i = 0; i < 6; ++i)
    scanf("%d", &a[i]);
}

void arrange(int &c1, int &c2, int &c3) {
  if (b[0] >= b[2] && b[0] >= b[4])
    c1 = 0;
  if (b[2] >= b[0] && b[2] >= b[4])
    c1 = 2;
  if (b[4] >= b[0] && b[4] >= b[2])
    c1 = 4;
  if (b[4] <= b[0] && b[4] <= b[2])
    c3 = 4;
  if (b[2] <= b[0] && b[2] <= b[4])
    c3 = 2;
  if (b[0] <= b[2] && b[0] <= b[4])
    c3 = 0;
  c2 = (c1 ^ c3 ^ 0 ^ 2 ^ 4);
}

void putu(int c) {
  printf("%c", C[c]);
  --b[c];
  while (a[L[c]] > 0) {
    --a[L[c]];
    printf("%c%c", C[L[c]], C[c]);
  }
}

void solve() {
  b[0] = a[0] - a[3];
  b[2] = a[2] - a[5];
  b[4] = a[4] - a[1];
  if (b[0] < 0 || b[2] < 0 || b[4] < 0 || b[0] + b[2] < b[4] ||
      b[0] + b[4] < b[2] || b[2] + b[4] < b[0]) {
    printf("IMPOSSIBLE\n");
    return;
  }
  int c1, c2, c3;
  arrange(c1, c2, c3);
  if (b[c1] == 0) {
    if ((a[1] > 0 && a[3] > 0) || (a[1] > 0 && a[5] > 0) ||
        (a[3] > 0 && a[5] > 0)) {
      printf("IMPOSSIBLE\n");
      return;
    }
    if (a[1] > 0) {
      for (int i = 1; i <= a[1]; ++i)
        printf("%c%c", C[1], C[4]);
    }
    if (a[3] > 0) {
      for (int i = 1; i <= a[3]; ++i)
        printf("%c%c", C[3], C[0]);
    }
    if (a[5] > 0) {
      for (int i = 1; i <= a[5]; ++i)
        printf("%c%c", C[5], C[2]);
    }
    printf("\n");
    return;
  }
  while (b[0] + b[2] + b[4] + a[1] + a[3] + a[5] > 0) {
    if (b[c1] == b[c2] + b[c3]) {
      putu(c1);
      if (b[c3] > 0)
        putu(c3);
      else
        putu(c2);
    } else {
      putu(c1);
      putu(c2);
      putu(c3);
    }
  }
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