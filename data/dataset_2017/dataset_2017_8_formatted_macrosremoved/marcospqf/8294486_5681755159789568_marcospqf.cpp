#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;
typedef long long int ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
const ld pi = acos(-1);
const int MOD = 1e9 + 9;
int n;
ll dist[110], vel[110], d[110][110];
ld resp[110];
double graph[110][110];
ld dij(int b, int e) {
  for (int i = 0; i < 110; i++)
    resp[i] = LINF;
  priority_queue<pair<double, int>, vector<pair<double, int>>,
                 greater<pair<double, int>>>
      pq;
  resp[b] = 0;
  pq.push(make_pair(0, b));
  while (!pq.empty()) {
    pair<double, int> topo = pq.top();
    pq.pop();
    int u = topo.second;
    double cost = topo.first;
    for (int v = 1; v <= n; v++) {
      if (v == u)
        continue;
      if (graph[u][v] == -1)
        continue;
      if (resp[v] > resp[u] + graph[u][v] + 1e-9) {
        resp[v] = resp[u] + graph[u][v];
        pq.push(make_pair(resp[v], v));
      }
    }
  }
  return resp[e];
}
void solve() {
  int q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++)
    cin >> dist[i] >> vel[i];

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      cin >> d[i][j];

  for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) {
        if (d[i][k] == -1 or d[k][j] == -1)
          continue;

        if (d[i][j] > d[i][k] + d[k][j])
          d[i][j] = d[i][k] + d[k][j];

        if (d[i][j] == -1)
          d[i][j] = d[i][k] + d[k][j];
      }

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      if (d[i][j] > dist[i] or d[i][j] == -1)
        graph[i][j] = -1;
      else
        graph[i][j] = d[i][j] / (double)vel[i];

  cout << fixed << setprecision(10);
  /*	for(int i=1;i<=n;i++){
                  for(int j=1;j<=n;j++){
                          cout<<graph[i][j]<<" ";
                  }
                  cout<<endl;
          }*/

  for (int i = 0; i < q; i++) {
    int b, e;
    scanf("%d%d", &b, &e);
    cout << dij(b, e) << " ";
  }
  cout << endl;
}
int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }

  return 0;
}
