#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

#define fi first
#define se second
typedef long long LL;
typedef long double LD;

LL T, N, K, a[30], ans[30];

int main() {
  ifstream fin("input.in");
  ofstream fout("output.out");
  fin >> T;

  int t, i, j;
  for (t = 1; t <= T; t++) {
    fout << "Case #" << t << ": ";
    fin >> N;

    K = 0;
    memset(a, 0, sizeof(a));
    while (N != 0) {
      a[++K] = N % 10;
      N /= 10;
    }

    bool valid = 1;
    for (i = K; i > 0 && valid; i--) {
      if (a[i] - 1 >= a[i + 1]) {
        for (j = K; j > i; j--)
          ans[j] = a[j];
        ans[i] = a[i] - 1;
        for (j = i - 1; j > 0; j--)
          ans[j] = 9;
      }

      if (a[i] < a[i + 1])
        valid = 0;
    }

    if (valid) {
      for (i = 1; i <= K; i++)
        ans[i] = a[i];
    }

    while (ans[K] == 0)
      K--;

    for (i = K; i > 0; i--)
      fout << ans[i];
    fout << "\n";
  }
  return 0;
}
