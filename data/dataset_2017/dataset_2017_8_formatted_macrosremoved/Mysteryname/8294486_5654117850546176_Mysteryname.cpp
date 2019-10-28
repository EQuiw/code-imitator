
/*
Contest: Google Code Jam 2017 [Round 1B]
*/

#include <algorithm>
#include <stdio.h>
#include <vector>
using namespace std;

int n;
int r, o, y, g, b, v;

vector<char> current;

char color[12] = "XRYOBVGX";
int cnt[12];

bool mycmp(const int &ls, const int &rs) { return cnt[ls] > cnt[rs]; }

void noGroupSolver() {
  char test[1010];
  test[n] = '\0';
  int tmp[4] = {1, 2, 4, 99};
  sort(tmp, tmp + 3, mycmp);
  if (cnt[tmp[0]] > n / 2) {
    printf("IMPOSSIBLE\n");
    return;
  } // Fail
  int high = cnt[tmp[0]];
  int lastCell = 2 * high - 1;
  int spaceLeft = n - lastCell;
  int det = spaceLeft / 2;
  int low = cnt[tmp[2]];
  if (low < det) {
    printf("IMPOSSIBLE\n");
    return;
  } // Fail
  for (int i = 0; i < high; i++)
    test[2 * i] = color[tmp[0]];
  // Big Gap Solver
  for (int i = 2 * (high - 1) + 1; i < n; i++) {
    // printf("FINDING: %d\n",i);
    if (i % 2 == 1) {
      test[i] = color[tmp[1]];
    } else {
      test[i] = color[tmp[2]];
      low--;
    }
  }
  // Space
  for (int i = 1; i < high; i++) {
    if (low > 0) {
      test[2 * i - 1] = color[tmp[2]];
      low--;
    } else
      test[2 * i - 1] = color[tmp[1]];
  }
  printf("%s\n", test);
}

void each() {
  scanf("%d", &n);
  scanf("%d%d%d%d%d%d", &r, &o, &y, &g, &b, &v);
  cnt[1] = r;
  cnt[2] = y;
  cnt[3] = o;
  cnt[4] = b;
  cnt[5] = v;
  cnt[6] = g;
  int special = o + v + g;
  // printf("Special Count: %d\n",special);
  if (special > n / 2) {
    printf("IMPOSSIBLE\n");
    return;
  } // Fail
  if (special == 0) {
    noGroupSolver();
    return;
  }
  // SMALL INPUT HAS NO MULTI COLOR!
}

int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-Small.txt", "w", stdout);
  int tc;
  scanf("%d", &tc);
  for (int t = 1; t <= tc; t++) {
    printf("Case #%d: ", t);
    each();
  }
  return 0;
}
