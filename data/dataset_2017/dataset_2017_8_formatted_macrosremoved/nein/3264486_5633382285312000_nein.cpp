#include <bits/stdc++.h>
using std::pair;
using std::vector;
char str[20];
int n;
pair<vector<int>, bool> dy[20][2][2][10];
bool chk[20][2][2][10];

pair<vector<int>, bool> go(int idx, bool start, bool less, int num) {
  if (idx == n) {
    return {{}, start};
  }
  auto &ret = dy[idx][start][less][num];
  if (chk[idx][start][less][num]) {
    return ret;
  }
  chk[idx][start][less][num] = true;

  if (start) {
    if (less) {
      for (int i = 9; i >= num; i--) {
        auto p = go(idx + 1, true, true, i);
        if (p.second) {
          ret = p;
          ret.first.push_back(i);
          break;
        }
      }
    } else {
      for (int i = str[idx]; i >= num; i--) {
        auto p = go(idx + 1, true, str[idx] != i, i);
        if (p.second) {
          ret = p;
          ret.first.push_back(i);
          break;
        }
      }
    }

  } else {
    auto p = go(idx, true, less, 1);
    if (p.second) {
      ret = p;
    } else {
      ret = go(idx + 1, false, true, 0);
    }
  }
  return ret;
}

int main() {
  int tc;
  scanf("%d", &tc);
  int q = 0;
  while (tc--) {
    memset(chk, 0, sizeof(chk));
    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
          for (int p = 0; p < 10; p++) {
            dy[i][j][k][p].first.clear();
            dy[i][j][k][p].second = 0;
          }
        }
      }
    }
    scanf("%s", str);
    n = strlen(str);
    for (int i = 0; i < n; i++) {
      str[i] -= '0';
    }
    auto ans = go(0, 0, 0, 0).first;
    std::reverse(ans.begin(), ans.end());
    q++;
    printf("Case #%d: ", q);
    for (int i : ans) {
      printf("%d", i);
    }
    printf("\n");
  }
}
