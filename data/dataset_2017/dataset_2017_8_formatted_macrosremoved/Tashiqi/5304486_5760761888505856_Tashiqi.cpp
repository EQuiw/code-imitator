#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
static const long long D = 1000000007;

int main() {
  long long T, R, C, i, j;
  cin >> T;
  for (long long t = 0; t < T; ++t) {
    cin >> R >> C;
    string foo;
    for (i = 0; i < C; ++i)
      foo += '?';
    vector<string> V(R), res(R, foo);
    vector<long long> X(R);
    vector<vector<long long>> Y(R, vector<long long>(C));
    for (i = 0; i < R; ++i)
      cin >> V[i];
    for (i = 0; V[i] == foo; ++i) {
    }
    for (j = 0; j < R; ++j) {
      if (V[j] != foo)
        i = j;
      X[j] = i;
    }
    for (long long k = 0; k < R; ++k) {
      for (i = 0; V[X[k]][i] == '?'; ++i) {
      }
      for (j = 0; j < C; ++j) {
        if (V[X[k]][j] != '?')
          i = j;
        res[k][j] = V[X[k]][i];
      }
    }
    cout << "Case #" << t + 1 << ":" << endl;
    for (auto &l : res)
      cout << l << endl;
  }

  return 0;
}
