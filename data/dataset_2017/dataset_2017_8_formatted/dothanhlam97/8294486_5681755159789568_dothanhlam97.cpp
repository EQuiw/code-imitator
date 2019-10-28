#include <bits/stdc++.h>
#define fi(a, b, c) for (int a = b; a <= c; a++)
#define fii(a, b, c) for (int a = b; a < c; a++)
#define pb push_back
#define mp make_pair

const int N = 1000;
typedef long long ll;

using namespace std;

double dp[N];
ll sum[N], f[N], d[N][N];
int q, n;
ll w[N], s[N];

void solve() {
  fi(i, 1, n) dp[i] = 1000000000000009;
  f[1] = 0;
  fi(i, 2, n) f[i] = f[i - 1] + d[i - 1][i];
  dp[1] = 0.0;
  fi(i, 1, n) {
    fi(j, i + 1, n) {
      int sum = f[j] - f[i];
      if (sum > w[i])
        break;
      dp[j] = min(dp[j], dp[i] + (double)sum / (double)s[i]);
    }
  }
}

int main() {
  int query;
  scanf("%d", &query);
  fi(t, 1, query) {
    scanf("%d %d", &n, &q);
    fi(i, 1, n) scanf("%d %d", &w[i], &s[i]);
    fi(i, 1, n) fi(j, 1, n) scanf("%d", &d[i][j]);
    int u, v;
    fi(i, 1, q) {
      scanf("%d %d", &u, &v);
      solve();
    }
    printf("Case #%d: %0.9lf\n", t, dp[n]);
  }
}