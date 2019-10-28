#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:100000000000")
#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;
#define FR(i, n) for (int(i) = 0; (i) < (n); (i)++)
#define FOR(i, c, n) for (int(i) = (c); (i) < (n); (i)++)
#define REP(it, v, cont)                                                       \
  for (cont::iterator(it) = (v).begin(); (it) != (v).end(); ++(it))
#define CLR(a, c) memset((a), (c), sizeof(a))
#define ALL(v) (v).begin(), (v).end()
#define SQR(a) ((a) * (a))
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;

int findmini(int x, int s) {
  int res = (x * 10) / (11 * s);
  if ((x * 10) % (11 * s) == 0)
    return res;
  return res + 1;
}
int findmaxi(int x, int s) {
  int res = (x * 10) / (9 * s);
  return res;
}

#define M 128
#define N 128

bool graph[M][N];
bool seen[N];
int matchL[M], matchR[N];
int n, p;

bool bpm(int u) {
  for (int v = 0; v < p; v++)
    if (graph[u][v]) {
      if (seen[v])
        continue;
      seen[v] = true;

      if (matchR[v] < 0 || bpm(matchR[v])) {
        matchL[u] = v;
        matchR[v] = u;
        return true;
      }
    }
  return false;
}

int main() {
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
  int Tcas;
  cin >> Tcas;
  FR(cas, Tcas) {
    printf("Case #%d: ", cas + 1);
    cin >> n >> p;
    vector<int> ingredients;
    FR(i, n) {
      int x;
      cin >> x;
      ingredients.push_back(x);
    }
    int mini[100][100] = {0};
    int maxi[100][100] = {0};
    CLR(mini, 0);
    CLR(maxi, 0);
    FR(i, n) {
      vector<int> temp;
      FR(j, p) {
        int x;
        cin >> x;
        temp.push_back(x);
      }
      sort(ALL(temp));
      FR(j, p) {
        mini[i][j] = findmini(temp[j], ingredients[i]);
        maxi[i][j] = findmaxi(temp[j], ingredients[i]);
        if (mini[i][j] > maxi[i][j])
          mini[i][j] = maxi[i][j] = -1;
      }
    }
    CLR(graph, false);
    FR(i, p) FR(j, p) {
      if (mini[0][i] <= 0 || mini[1][j] <= 0)
        continue;
      if (max(mini[0][i], mini[1][j]) <= min(maxi[0][i], maxi[1][j]))
        graph[i][j] = true;
    }
    if (n == 2) {
      memset(matchL, -1, sizeof(matchL));
      memset(matchR, -1, sizeof(matchR));
      int cnt = 0;
      for (int i = 0; i < p; i++) {
        memset(seen, 0, sizeof(seen));
        if (bpm(i))
          cnt++;
      }
      cout << cnt << endl;
    } else {
      int sum = 0;
      FR(i, p) if (mini[0][i] != -1 && mini[0][i] <= maxi[0][i]) sum++;
      cout << sum << endl;
    }
  }
}