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
#define sc(a) scanf("%d", &a)
#define sc2(a, b) scanf("%d%d", &a, &b)
#define sc3(a, b, c) scanf("%d%d%d", &a, &b, &c)
#define scs(a) scanf("%s", a)
#define pri(x) printf("%d\n", x)
#define prie(x) printf("%d ", x)
#define mp make_pair
#define pb push_back
#define BUFF ios::sync_with_stdio(false);
#define db(x) cerr << #x << " == " << x << endl
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
int v[7], n;
int resp[1010];
// 0 red 1 yellow 2 blue
int qtdaux[3], qtd[3];
int pegamaior(int naopode, int b) {
  int aux = 0;
  int ret = 0;
  for (int i = 0; i < 3; i++) {
    if (i == naopode)
      continue;
    if (aux < qtd[i]) {
      aux = qtd[i];
      ret = i;
    } else if (aux == qtd[i] and aux > 0 and i == b) {
      ret = i;
    }
  }
  if (aux == 0)
    return -1;
  return ret;
}
bool simula(int x) {
  qtd[0] = qtdaux[0];
  qtd[1] = qtdaux[1];
  qtd[2] = qtdaux[2];
  memset(resp, -1, sizeof(resp));
  resp[0] = x;
  qtd[x]--;
  for (int i = 1; i < n; i++) {
    int y = pegamaior(resp[i - 1], x);
    if (y == -1)
      return 0;
    resp[i] = y;
    qtd[y]--;
  }
  return resp[0] != resp[n - 1];
}
void printaresp() {
  for (int i = 0; i < n; i++) {
    if (resp[i] == 0)
      cout << "R";
    else if (resp[i] == 1)
      cout << "Y";
    else
      cout << "B";
  }
  cout << endl;
}
void solve() {
  sc(n);
  for (int i = 0; i < 6; i++)
    sc(v[i]);
  qtdaux[0] = v[0];
  qtdaux[1] = v[2];
  qtdaux[2] = v[4];
  for (int i = 0; i < 3; i++) {
    if (qtdaux[i] > 0) {
      bool x = simula(i);
      if (x) {
        printaresp();
        return;
      }
    }
  }
  cout << "IMPOSSIBLE" << endl;
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
