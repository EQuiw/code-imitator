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
const int Maxn = 110, Maxk = 5010, Mo = 1e9 + 7, oo = INT_MAX >> 2;
const int sp[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int T;
using namespace std;
long long f[1000][10];
int n, m, k, cs, ans;
int N, K;
string st;
char mp[100][100];
int L[100], R[100], U[100], D[100];
vector<int> color;
void pushl(int id) {
  while (L[id] > 1) {
    int ck = 1;
    for (int i = U[id]; ck && i <= D[id]; i++) {
      ck &= (mp[i][L[id] - 1] == '?');
    }
    if (ck)
      L[id]--;
    else
      break;
  }
}
void pushr(int id) {
  while (R[id] < m) {
    int ck = 1;
    for (int i = U[id]; ck && i <= D[id]; i++) {
      ck &= (mp[i][R[id] + 1] == '?');
    }
    if (ck)
      R[id]++;
    else
      break;
  }
}
void pushu(int id) {
  while (U[id] > 0) {
    int ck = 1;
    for (int i = L[id]; ck && i <= R[id]; i++) {
      ck &= (mp[U[id] - 1][i] == '?');
    }
    if (ck)
      U[id]--;
    else
      break;
  }
}
void pushd(int id) {
  while (D[id] < n) {
    int ck = 1;
    for (int i = L[id]; ck && i <= R[id]; i++) {
      ck &= (mp[D[id] + 1][i] == '?');
    }
    if (ck)
      D[id]++;
    else
      break;
  }
}
int main() {
  cin >> T;
  while (T--) {
    printf("Case #%d: \n", ++cs);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
      cin >> (mp[i] + 1);
    for (int i = 0; i <= 27; i++) {
      L[i] = U[i] = 10000;
      R[i] = D[i] = -1;
    }
    color.clear();
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        if (mp[i][j] == '?')
          continue;
        int id = mp[i][j] - 'A';
        color.push_back(id);
        L[id] = min(L[id], j);
        R[id] = max(R[id], j);
        U[id] = min(U[id], i);
        D[id] = max(D[id], i);
      }
    for (int i = 0; i < color.size(); i++) {
      pushl(color[i]);
      pushr(color[i]);
      pushu(color[i]);
      pushd(color[i]);
      for (int x = U[color[i]]; x <= D[color[i]]; x++)
        for (int y = L[color[i]]; y <= R[color[i]]; y++)
          mp[x][y] = 'A' + color[i];
    }
    for (int i = 1; i <= n; i++) {
      cout << (mp[i] + 1) << endl;
    }
  }
  return 0;
}
