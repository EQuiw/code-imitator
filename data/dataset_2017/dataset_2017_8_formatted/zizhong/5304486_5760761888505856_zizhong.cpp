#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <cassert>
#include <unordered_map>
#endif
#include <cmath>
#include <ctime>
#include <iomanip>
#include <queue>
#include <sstream>
#include <stack>
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<int, PII> PIP;
typedef long long ll;
typedef pair<ll, ll> PLL;

void solve(int ncase) {
  cout << "Case #" << ncase << ":" << endl;

  int r, c;
  cin >> r >> c;
  vector<string> cake(r);
  vector<PII> letter;
  for (int i = 0; i < r; i++) {
    cin >> cake[i];
    for (int j = 0; j < c; j++) {
      if (cake[i][j] != '?') {
        letter.push_back(PII(i, j));
      }
    }
  }
  vector<string> ret = cake;
  for (auto p : letter) {
    int x1 = p.first - 1, x2 = p.first + 1;
    int y1 = p.second - 1, y2 = p.second + 1;
    while (x1 >= 0) {
      bool flag = false;
      for (int i = 0; i < c; i++)
        if (cake[x1][i] != '?')
          flag = true;
      if (flag == true)
        break;
      x1--;
    }
    while (x2 < r) {
      bool flag = false;
      for (int i = 0; i < c; i++)
        if (cake[x2][i] != '?')
          flag = true;
      if (flag == true)
        break;
      x2++;
    }
    while (y1 >= 0 && cake[p.first][y1] == '?')
      y1--;
    while (y2 < c && cake[p.first][y2] == '?')
      y2++;
    for (int i = x1 + 1; i < x2; i++) {
      for (int j = y1 + 1; j < y2; j++) {
        ret[i][j] = cake[p.first][p.second];
      }
    }
  }
  for (int i = 0; i < r; i++) {
    cout << ret[i] << endl;
  }
}

int main() {
  // ios::sync_with_stdio(false);
  cout << std::fixed;
  // cout << setprecision(16) << endl;
#ifdef _zzz_
  // freopen("in.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
#endif
  int T = 1;
  scanf("%d", &T);
  // cin >> T;
  // precalc();
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}
