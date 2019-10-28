#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
const double pi = acos(-1.), eps = 1e-6;
const int Maxn = 110, Maxk = 5010, Mo = 1e9 + 7, oo = 2e9 + 1;
const int sp[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int T;
using namespace std;
// ll f[Maxn][Maxn][2],vis[Maxn][Maxn][2];
int n, m, k, cs;
struct Rec {
  int a, b, l;
};
// int check(double speed){
// 	rep(i,1,N){
// 		if (v[i] <= speed){
// 			if (D - S[i]) / v[i]
// 		}
// 	}
// }
// int N, R, O, Y, G, B, V;
int N, Q;
int num[10], ans[Maxn];
long long d[Maxn][Maxn];
int S[Maxn], E[Maxn];
double t[Maxn][Maxn];
vector<int> w[1010];
int main() {
  cin >> T;
  while (T--) {
    printf("Case #%d: ", ++cs);
    cin >> n >> Q;
    for (int i = 1; i <= n; i++)
      cin >> E[i] >> S[i];
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) {
        cin >> d[i][j];
        if (d[i][j] == -1)
          d[i][j] = oo;
      }
    for (int i = 1; i <= n; i++)
      d[i][i] = 0;

    for (int k = 1; k <= n; k++)
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
          d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    // rep(i,1,n){
    // 	rep(j,1,n) cout << d[i][j]<<" ";
    // 	cout << endl;
    // }
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) {
        if (d[i][j] > E[i])
          t[i][j] = 1e100;
        else
          t[i][j] = 1. * d[i][j] / S[i];
      }
    for (int k = 1; k <= n; k++)
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
          t[i][j] = min(t[i][j], t[i][k] + t[k][j]);
    for (int i = 1; i <= Q; i++) {
      int u, v;
      cin >> u >> v;
      printf("%.7f", t[u][v]);
      if (i < Q)
        cout << " ";
    }
    cout << endl;
  }
  return 0;
}
