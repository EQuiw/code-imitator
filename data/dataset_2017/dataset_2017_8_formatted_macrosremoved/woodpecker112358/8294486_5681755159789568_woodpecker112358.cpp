#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;
typedef long long mint;
typedef unsigned long long umint;
int main() {
  freopen("C-small-attempt0.in", "r", stdin);
  freopen("Cout.txt", "w", stdout);
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    int n, q;
    cin >> n >> q;
    vector<int> E(n), S(n);
    for (int i = 0; i < (n); i++) {
      cin >> E[i] >> S[i];
    }
    vector<vector<mint>> v(n, vector<mint>(n));
    for (int i = 0; i < (n); i++) {
      for (int j = 0; j < (n); j++) {
        scanf("%lld", &v[i][j]);
      }
      v[i][i] = 0;
    }

    for (int k = 0; k < (n); k++) {
      for (int i = 0; i < (n); i++) {
        for (int j = 0; j < (n); j++) {
          if (v[i][k] != -1 && v[k][j] != -1) {
            if (v[i][j] == -1 || v[i][j] > v[i][k] + v[k][j]) {
              v[i][j] = v[i][k] + v[k][j];
            }
          }
        }
      }
    }
    /*Rep(i,n)
    {
        Rep(j,n)
        {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }*/
    vector<vector<double>> d(n, vector<double>(n, 0.0));
    for (int i = 0; i < (n); i++) {
      for (int j = 0; j < (n); j++) {
        if (E[i] >= v[i][j] && v[i][j] != -1) {
          d[i][j] = v[i][j] / (S[i] * 1.0);
        } else {
          d[i][j] = -1.0;
        }
      }
    }
    for (int k = 0; k < (n); k++) {
      for (int i = 0; i < (n); i++) {
        for (int j = 0; j < (n); j++) {
          if (d[i][k] >= -.5 && d[k][j] >= -.5) {
            if (d[i][j] < -.5 || d[i][j] > d[i][k] + d[k][j]) {
              d[i][j] = d[i][k] + d[k][j];
            }
          }
        }
      }
    }
    /*cout << endl;
    Rep(i,n)
    {
        Rep(j,n)
        {
            cout << d[i][j] << " ";
        }
        cout << endl;
    }*/
    printf("Case #%d: ", t);
    int uu, vv;
    for (int i = 0; i < (q); i++) {
      cin >> uu >> vv;
      printf(" %.9f", d[uu - 1][vv - 1]);
    }
    cout << endl;
  }
  return 0;
}
