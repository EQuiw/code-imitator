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
char tab[30][30];
int n, m;
void preenche_cima(int x, int y) {
  for (int i = x - 1; i >= 0; i--) {
    if (tab[i][y] == '?') {
      tab[i][y] = tab[x][y];
    } else
      break;
  }
}
void preenche_baixo(int x, int y) {
  for (int i = x + 1; i < n; i++) {
    if (tab[i][y] == '?') {
      tab[i][y] = tab[x][y];
    } else
      break;
  }
}
void process() {
  for (int j = 0; j < m; j++)
    for (int i = 0; i < n; i++)
      if (tab[i][j] != '?') {
        preenche_cima(i, j);
        preenche_baixo(i, j);
      }
  char last = '0';
  int poe = 0;
  for (int j = 0; j < m; j++) {
    if (tab[0][j] == '?') {
      if (last == '0') {
        continue;
      } else {
        for (int i = 0; i < n; i++)
          tab[i][j] = tab[i][j - 1];
      }
    } else {
      if (last == '0') {
        for (int i = 0; i < n; i++)
          for (int k = 0; k < j; k++)
            tab[i][k] = tab[i][j];
      }
      last = tab[0][j];
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << tab[i][j];
    }
    cout << endl;
  }
}
void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> tab[i][j];
  process();
}
int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cout << "Case #" << i << ":" << endl;
    solve();
  }
  return 0;
}
