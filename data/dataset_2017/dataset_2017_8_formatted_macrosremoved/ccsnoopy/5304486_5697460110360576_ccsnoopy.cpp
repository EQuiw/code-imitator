#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long LL;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
int unit[52];
int wt[52][52];
int mn[52][52], mx[52][52];
int f;
vii adjList[1010];
int par[1010];
int n, p;

void open() {
  freopen("D:/OneDrive/Code/GCJ/B-small-attempt0 (1).in", "r", stdin);
  freopen("D:/OneDrive/Code/GCJ/out.txt", "w", stdout);
}

void augment(int x) {
  if (par[x] != x) {
    for (int i = 0; i < adjList[par[x]].size(); i++) {
      if (adjList[par[x]][i].first == x) {
        f = min(f, adjList[par[x]][i].second);
        break;
      }
    }
    augment(par[x]);
    for (int i = 0; i < adjList[par[x]].size(); i++) {
      if (adjList[par[x]][i].first == x) {
        adjList[par[x]][i].second -= f;
        break;
      }
    }

    for (int i = 0; i < adjList[x].size(); i++) {
      if (adjList[x][i].first == par[x]) {
        adjList[x][i].second += f;
        break;
      }
    }
  }
}

int maxflow() {
  int mf = 0;
  f = 0;
  while (true) {
    f = 0;
    memset(par, -1, sizeof(par));
    queue<int> q;
    q.push(n * p);
    par[n * p] = n * p;
    bool found = false;

    while (!q.empty()) {
      int node = q.front();
      // cout <<"cur : " << node << endl;
      q.pop();
      for (int i = 0; i < adjList[node].size(); i++) {

        int nx = adjList[node][i].first;
        int cap = adjList[node][i].second;
        // cout << nx << " " << cap << endl;
        if (cap > 0 && par[nx] == -1) {
          par[nx] = node;
          if (nx == n * p + 1) {
            f = 1000000000;
            augment(nx);
            found = true;

            break;
          }
          q.push(nx);
        }
      }
      if (found)
        break;
    }

    if (f == 0)
      break;
    mf += f;
  }

  return mf;
}

int main(void) {
  open();
  int tc;
  scanf("%d", &tc);

  for (int ct = 1; ct <= tc; ct++) {
    map<int, int> mp;

    scanf("%d", &n);
    scanf("%d", &p);
    for (int i = 0; i < n; i++) {
      scanf("%d", &unit[i]);
    }

    memset(mn, -1, sizeof(mn));
    memset(mx, -1, sizeof(mx));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++) {
        scanf("%d", &wt[i][j]);
        int tmp1 = floor(1.0 * wt[i][j] / (0.9 * unit[i]));
        int tmp2 = ceil(1.0 * wt[i][j] / (1.1 * unit[i]));
        int bawah = min(tmp1, tmp2);
        int atas = max(tmp1, tmp2);
        // cout << bawah << " " << atas << endl;
        while (bawah <= atas) {
          if (bawah * 0.9 * unit[i] - 1e-9 <= 1.0 * wt[i][j] &&
              1.0 * wt[i][j] <= bawah * 1.1 * unit[i] + 1e-9)
            break;
          else
            bawah++;
        }

        // cout << bawah << " " << atas << endl;

        if (bawah > atas)
          continue;

        while (atas >= bawah) {
          if (atas * 0.9 * unit[i] - 1e-9 <= 1.0 * wt[i][j] &&
              1.0 * wt[i][j] <= atas * 1.1 * unit[i] + 1e-9)
            break;
          else
            atas--;
        }
        // cout <<"idx : " << i << endl;
        // cout << bawah << " " << atas << endl;
        mn[i][j] = bawah;
        mx[i][j] = atas;

        // while(mx[i][j] == -1 && )
      }
    }

    for (int i = 0; i < 1010; i++)
      adjList[i].clear();

    for (int i = 0; i < n - 1; i++) {
      for (int j = 0; j < p; j++) {
        if (mn[i][j] <= 0)
          continue;
        for (int k = 0; k < p; k++) {
          if (mn[i + 1][k] <= 0)
            continue;
          // printf("%d %d %d %d\n", mn[i][j], mx[i][j], mn[i+1][k],
          // mx[i+1][k]);
          if ((mn[i][j] <= mn[i + 1][k] && mn[i + 1][k] <= mx[i][j]) ||
              (mn[i + 1][k] <= mn[i][j] && mn[i][j] <= mx[i + 1][k])) {
            // cout << (i * p + j) << " to " << ((i+1)*p + k) << endl;
            adjList[i * p + j].push_back(ii((i + 1) * p + k, 1));
            adjList[(i + 1) * p + k].push_back(ii(i * p + j, 0));
          }
        }
      }
    }

    for (int j = 0; j < p; j++) {
      // source + to sink.
      if (mn[0][j] > 0) {
        adjList[n * p].push_back(ii(j, 1));
        adjList[j].push_back(ii(n * p, 0));
      }

      if (mn[n - 1][j] > 0) {
        adjList[(n - 1) * p + j].push_back(ii(n * p + 1, 1));
        adjList[n * p + 1].push_back(ii((n - 1) * p + j, 0));
      }
    }

    printf("Case #%d: %d\n", ct, maxflow());
    cerr << "Test " << ct << " done \n";
  }
  return 0;
}
