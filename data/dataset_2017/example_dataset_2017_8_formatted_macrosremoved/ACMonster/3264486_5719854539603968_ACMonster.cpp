// Problem D

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int get() {
  char c;
  while (c = getchar(), c != '-' && (c < '0' || c > '9'))
    ;
  bool flag = (c == '-');
  if (flag)
    c = getchar();
  int x = 0;
  while (c >= '0' && c <= '9') {
    x = x * 10 + c - '0';
    c = getchar();
  }
  return flag ? -x : x;
}

char sym[4] = {'.', 'x', '+', 'o'};

bool row[200], column[200], flag[200];
int a[100][100], b[100][100];
int peer[200];
vector<int> g[200];

int num(char c) {
  for (int i = 0; i < 4; i++)
    if (sym[i] == c)
      return i;
  return -1;
}

bool dfs(int x) {
  if (x == -1)
    return true;
  if (flag[x] || row[x])
    return false;
  flag[x] = true;
  for (int i = 0; i < g[x].size(); i++) {
    int y = g[x][i];
    if (column[y])
      continue;
    if (dfs(peer[y])) {
      peer[y] = x;
      return true;
    }
  }
  return false;
}

int main() {
  int totalTest = get();
  for (int test = 1; test <= totalTest; test++) {
    int n = get(), total = get(), ans = 0;

    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    for (int i = 0; i < total; i++) {
      char x;
      while (x = getchar(), num(x) == -1)
        ;
      int r = get() - 1, c = get() - 1;
      a[r][c] = b[r][c] = num(x);
      if (a[r][c] == 3)
        ans += 2;
      else if (a[r][c] > 0)
        ans++;
    }

    memset(row, 0, sizeof(row));
    memset(column, 0, sizeof(column));
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (a[i][j] & 1)
          row[i] = column[j] = true;
    vector<int> validRow, validColumn;
    validRow.clear();
    validColumn.clear();
    for (int i = 0; i < n; i++)
      if (!row[i])
        validRow.push_back(i);
    for (int i = 0; i < n; i++)
      if (!column[i])
        validColumn.push_back(i);
    int cnt = min(validRow.size(), validColumn.size());
    ans += cnt;
    for (int i = 0; i < cnt; i++)
      b[validRow[i]][validColumn[i]] |= 1;

    memset(row, 0, sizeof(row));
    memset(column, 0, sizeof(column));
    int m = n * 2 - 1;
    for (int i = 0; i < m; i++)
      g[i].clear();
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        int r = i + j;
        int c = i - j + n - 1;
        g[r].push_back(c);
        if (a[i][j] & 2)
          row[r] = column[c] = true;
      }

    memset(peer, -1, sizeof(peer));
    for (int i = 0; i < m; i++) {
      if (row[i])
        continue;
      memset(flag, 0, sizeof(flag));
      if (dfs(i))
        ans++;
    }
    for (int i = 0; i < m; i++)
      if (!column[i] && peer[i] != -1) {
        int sum = peer[i], diff = i;
        int r = (sum + diff - (n - 1)) / 2;
        int c = sum - r;
        b[r][c] |= 2;
      }

    int changes = 0;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (b[i][j] != a[i][j])
          changes++;

    printf("Case #%d: %d %d\n", test, ans, changes);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (b[i][j] != a[i][j])
          printf("%c %d %d\n", sym[b[i][j]], i + 1, j + 1);
  }
  return 0;
}
