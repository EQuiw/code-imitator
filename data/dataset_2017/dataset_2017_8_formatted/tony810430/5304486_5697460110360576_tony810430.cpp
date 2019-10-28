#include <algorithm>
#include <cmath>
#include <cstring>
#include <stdio.h>

using namespace std;

struct XD {
  long long value;
  int mini;
  int maxi;
};

int T;
int N, P;

long long R[2000];
XD Q[1005][1005];

int serveMin(long long target, long long v) {
  int left = 1, right = 1000005;
  int mid;
  int res = -1;

  for (int i = 0; i <= 1000; i++) {
    mid = (left + right) / 2;
    if (mid * v * 9 <= target * 10 && target * 10 <= mid * v * 11) {
      res = (res == -1) ? mid : min(mid, res);
    }

    if (target * 10 <= mid * v * 11) {
      right = mid;
    } else {
      left = mid;
    }
  }

  return res;
}

int visit[2000];

void dfs(int v, int &ans) {
  if (v == P) {
    int cnt = 0;
    for (int i = 0; i < P; i++) {
      XD a = Q[0][i];
      XD b = Q[1][visit[i]];
      if (a.mini == -1 || b.mini == -1)
        continue;
      if (a.maxi > b.maxi) {
        swap(a, b);
      }
      if (b.mini <= a.maxi)
        cnt++;
    }
    ans = max(ans, cnt);
  }
  for (int i = 0; i < P; i++) {
    if (visit[i] == -1) {
      visit[i] = v;
      dfs(v + 1, ans);
      visit[i] = -1;
    }
  }
}

int solve() {
  memset(visit, -1, sizeof(visit));
  int cnt = 0;
  if (N == 1) {
    for (int i = 0; i < P; i++) {
      if (Q[0][i].mini != -1) {
        cnt++;
      }
    }
  } else if (N == 2) {
    dfs(0, cnt);
  } else {
    cnt = -1;
  }
  return cnt;
}

int serveMax(long long target, long long v) {
  int left = 1, right = 1000005;
  int mid;
  int res = -1;

  for (int i = 0; i <= 1000; i++) {
    mid = (left + right) / 2;
    if (mid * v * 9 <= target * 10 && target * 10 <= mid * v * 11) {
      res = (res == -1) ? mid : max(mid, res);
    }

    if (mid * v * 9 <= target * 10) {
      left = mid;
    } else {
      right = mid;
    }
  }

  return res;
}

int main() {
  scanf(" %d", &T);

  for (int cas = 1; cas <= T; cas++) {
    scanf(" %d %d", &N, &P);
    for (int i = 0; i < N; i++) {
      scanf(" %lld", &R[i]);
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < P; j++) {
        scanf(" %lld", &Q[i][j].value);
        Q[i][j].mini = serveMin(Q[i][j].value, R[i]);
        Q[i][j].maxi = serveMax(Q[i][j].value, R[i]);
      }
    }

    int res = solve();
    printf("Case #%d: %d\n", cas, res);
  }

  return 0;
}