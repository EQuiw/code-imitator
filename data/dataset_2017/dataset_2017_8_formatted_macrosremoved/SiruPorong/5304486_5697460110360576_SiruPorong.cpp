#include <algorithm>
#include <stdio.h>

using namespace std;

int n, m, data[51], mp[51][51];
pair<int, int> mp2[51][51];
int check[51][2], mx;

void dfs(int node) {
  int i;
  if (node == m + 1) {
    int cnt = 0;
    for (i = 1; i <= m; i++) {
      if (mp2[1][i].first == -1 || mp2[2][check[i][1]].first == -1)
        continue;
      if (mp2[1][i].first <= mp2[2][check[i][1]].second &&
          mp2[2][check[i][1]].first <= mp2[1][i].second)
        cnt++;
    }

    if (cnt > mx) {
      mx = cnt;
    }
    return;
  }

  for (i = 1; i <= m; i++) {
    if (check[i][0] == 0) {
      check[i][0] = 1;
      check[node][1] = i;
      dfs(node + 1);
      check[i][0] = 0;
      check[node][1] = 0;
    }
  }
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t, i, j, k;

  scanf("%d", &t);

  for (int tt = 1; tt <= t; tt++) {
    scanf("%d%d", &n, &m);

    for (i = 1; i <= n; i++) {
      scanf("%d", &data[i]);
    }
    mx = 0;
    for (i = 1; i <= n; i++) {
      for (j = 1; j <= m; j++) {
        scanf("%d", &mp[i][j]);
        if (mp[i][j] >= data[i] * 9) {
          mp2[i][j] =
              make_pair(((mp[i][j] * 10 + 10) / 11 + data[i] - 1) / data[i],
                        (mp[i][j] * 10 + 8) / 9 / data[i]);
          mx++;
        } else {
          int node = mp[i][j] * 10 / 9 / data[i];
          if (data[i] * node * 9 / 10 <= mp[i][j] &&
              mp[i][j] <= data[i] * node * 11 / 10) {
            mp2[i][j] = make_pair(node, node);
            mx++;
          } else
            mp2[i][j] = make_pair(-1, -1);
        }
      }
    }

    if (n == 2) {
      mx = 0;
      dfs(1);
    }

    printf("Case #%d: %d\n", tt, mx);
  }
  return 0;
}
