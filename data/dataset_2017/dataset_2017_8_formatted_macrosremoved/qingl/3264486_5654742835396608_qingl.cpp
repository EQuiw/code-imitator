#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 1005;
int a[N];
int main() {
  freopen("C-small-1-attempt0.in", "r", stdin);
  freopen("out.txt", "w", stdout);
  int T, ca = 1, n, k;
  scanf("%d", &T);
  while (T--) {
    printf("Case #%d: ", ca++);
    scanf("%d%d", &n, &k);
    int p = 2, ps;
    a[0] = 0;
    a[1] = n + 1;
    for (int i = 0; i < k; i++) {
      int mx = -1;
      for (int j = 0; j < p - 1; j++) {
        if (a[j + 1] - a[j] > mx) {
          mx = a[j + 1] - a[j];
          ps = (a[j] + (mx - 2) / 2 + 1);
        }
      }
      a[p++] = ps;
      sort(a, a + p);
    }
    int h, r1, r2;
    for (int i = 0; i < p; i++) {
      if (a[i] == ps) {
        r1 = (a[i + 1] - a[i - 1] - 2) / 2;
        r2 = (a[i + 1] - a[i - 1] - 2) - r1;
      }
    }
    printf("%d %d\n", r2, r1);
  }
  return 0;
}
