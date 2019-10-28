#include <algorithm>
#include <assert.h>
#include <functional>
#include <iostream>
#include <map>
#include <math.h>
#include <memory.h>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> Pi;
int N, M, T, K, tc;
int p[1000];
void solve() {
  string s;
  cin >> s >> K;
  memset(p, 0, sizeof p);
  int cur = 0;
  int ans = 0;
  for (int i = 0; i <= s.size() - K; i++) {
    cur += p[i];
    if (cur % 2 == 0 && s[i] == '-') {
      ans++;
      cur++;
      p[i + K] = -1;
    } else if (cur % 2 == 1 && s[i] == '+') {
      ans++;
      cur++;
      p[i + K] = -1;
    }
  }
  for (int i = s.size() - K + 1; i < s.size(); i++) {
    cur += p[i];
    if (cur % 2 == 0 && s[i] == '-') {
      printf("IMPOSSIBLE\n");
      return;
    } else if (cur % 2 == 1 && s[i] == '+') {
      printf("IMPOSSIBLE\n");
      return;
    }
  }
  printf("%d\n", ans);
}

int main(void) {
  freopen("output.txt", "w", stdout);
  scanf("%d", &tc);
  for (int tcx = 1; tcx <= tc; tcx++) {
    printf("Case #%d: ", tcx);
    solve();
  }
}
