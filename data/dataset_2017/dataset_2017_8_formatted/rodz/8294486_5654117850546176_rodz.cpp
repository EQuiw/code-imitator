#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fi first
#define se second

using namespace std;

typedef pair<int, int> ii;
typedef long long ll;

const int N = 1010;
char color[N];
char ans[N];

int n, r, o, y, g, b, v;

int main() {
  int t, casecnt = 1;
  cin >> t;

  while (t--) {
    cin >> n >> r >> o >> y >> g >> b >> v;
    printf("Case #%d: ", casecnt++);

    char last;
    int m = max(r, max(b, y));
    if (r == m) {
      last = 'R';
      r--;
    } else if (b == m) {
      last = 'B';
      b--;
    } else {
      last = 'Y';
      y--;
    }
    ans[0] = last;
    for (int i = 1; i < n; i++) {
      if (last == 'R') {
        if (y > b) {
          ans[i] = 'Y';
          y--;
        } else {
          ans[i] = 'B';
          b--;
        }
      } else if (last == 'Y') {
        if (r > b) {
          ans[i] = 'R';
          r--;
        } else {
          ans[i] = 'B';
          b--;
        }
      } else if (last == 'B') {
        if (y > r) {
          ans[i] = 'Y';
          y--;
        } else {
          ans[i] = 'R';
          r--;
        }
      }
      last = ans[i];
    }

    if (min(r, min(y, b)) < 0)
      printf("IMPOSSIBLE\n");
    else {

      if (ans[n - 1] == ans[0])
        swap(ans[n - 1], ans[n - 2]);

      bool ok = true;
      for (int i = 0; i < n - 1 and ok; i++) {
        if (ans[i] == ans[i + 1])
          ok = false;
      }

      if (ok)
        for (int i = 0; i < n; i++)
          printf("%c", ans[i]);
      else
        printf("IMPOSSIBLE");

      printf("\n");
    }
  }
  return 0;
}
