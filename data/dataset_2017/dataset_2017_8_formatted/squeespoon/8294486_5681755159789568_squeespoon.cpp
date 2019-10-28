#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int maxn = 105;
const int INF = 2e9;

int n, q;

int e[maxn]; //	ÄÍÁ¦
int s[maxn]; //	ËÙ¶È

int d[maxn][maxn];

int dd[maxn][maxn];

int needEn[maxn];

void floyd() {
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (dd[i][k] != -1 && dd[k][j] != -1) {
          if (dd[i][j] == -1) {
            dd[i][j] = dd[i][k] + dd[k][j];
          } else {
            dd[i][j] = min(dd[i][k] + dd[k][j], dd[i][j]);
          }
        }
      }
    }
  }
}

double ans[maxn][1005];

struct node {
  int uu;
  int speed;
  int en;
  double time;
  node(int uu, int speed, int en, double time)
      : uu(uu), speed(speed), en(en), time(time) {}
  node() {}
};

void spfa(int u, int v) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= 1000; j++) {
      ans[i][j] = 1e18;
    }
  }

  ans[u][s[u]] = 0;
  queue<node> que;

  que.push(node(u, s[u], e[u], 0));

  while (que.size()) {
    node cur = que.front();
    que.pop();
    // cout<<"cur node "<<cur.uu<<" "<<cur.time<<endl;
    for (int i = 1; i <= n; i++) {
      if (d[cur.uu][i] != -1) {
        if (cur.en - d[cur.uu][i] >= needEn[i]) {
          if (cur.time + (d[cur.uu][i] + 0.0) / cur.speed < ans[i][cur.speed]) {
            ans[i][cur.speed] = cur.time + (d[cur.uu][i] + 0.0) / cur.speed;
            node newnd = node(i, cur.speed, cur.en - d[cur.uu][i],
                              cur.time + (d[cur.uu][i] + 0.0) / cur.speed);

            que.push(newnd);
          }
        }

        // change
        if (e[i] >= needEn[i]) {
          if (cur.time + (d[cur.uu][i] + 0.0) / cur.speed < ans[i][s[i]]) {
            ans[i][s[i]] = cur.time + (d[cur.uu][i] + 0.0) / cur.speed;
            node newnd = node(i, s[i], e[i],
                              cur.time + (d[cur.uu][i] + 0.0) / cur.speed);

            que.push(newnd);
          }
        }
      }
    }
  }
}

int main() {
  freopen("C-small-attempt1.in", "r", stdin);
  freopen("C-small-attempt1.out", "w", stdout);

  int t;
  cin >> t;
  int cas = 0;

  while (t--) {
    cas++;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
      cin >> e[i] >> s[i];
    }

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        cin >> d[i][j];
        dd[i][j] = d[i][j];
      }
    }

    floyd();

    printf("Case #%d: ", cas);

    while (q--) {
      int u, v;
      cin >> u >> v;

      for (int i = 1; i <= n; i++) {
        needEn[i] = INF;
        if (dd[i][v] != -1) {
          needEn[i] = dd[i][v];
        }
      }
      needEn[v] = 0;

      for (int k = 0; k < 100; k++)
        for (int i = 1; i <= n; i++) {
          for (int j = 1; j <= n; j++) {
            if (i == j)
              continue;
            if (dd[i][j] != -1 && dd[j][v] != -1) {
              needEn[i] = min(needEn[i], dd[i][j]);
            }
          }
        }

      /*for(int i=1;i<=n;i++){
              cout<<needEn[i]<<" ";
      }
      cout<<endl;
      */
      spfa(u, v);

      double res = 1e18;
      for (int i = 1; i <= 1000; i++) {
        res = min(res, ans[v][i]);
      }

      printf("%.8f", res);
      if (q) {
        printf(" ");
      }
      // cout<<res<<endl;
    }
    cout << endl;
  }
  return 0;
}
