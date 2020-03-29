#include <bits/stdc++.h>

using namespace std;

vector<int> w[2];

const int N = 100010;

int a[N];

int main() {
  int tt;
  scanf("%d", &tt);
  for (int cc = 1; cc <= tt; ++cc) {
    printf("Case #%d: ", cc);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < 2; ++i) {
      w[i].clear();
    }
    for (int i = 0; i < n; ++i) {
      int foo;
      scanf("%d", &foo);
      w[i % 2].push_back(foo);
    }
    for (int i = 0; i < 2; ++i) {
      sort(w[i].begin(), w[i].end());
      for (int j = 0; j < (int)w[i].size(); ++j) {
        a[2 * j + i] = w[i][j];
      }
    }
    int ans = -1;
    for (int i = n - 2; i >= 0; --i) {
      if (a[i] > a[i + 1]) {
        ans = i;
      }
    }
    if (ans == -1) {
      puts("OK");
    } else {
      printf("%d\n", ans);
    }
  }
}
