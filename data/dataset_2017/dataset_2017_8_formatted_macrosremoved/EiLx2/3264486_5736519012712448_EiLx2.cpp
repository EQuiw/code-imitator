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

typedef long long LL;
typedef long double LD;

int T, K;
string s;

char flip(char c) {
  if (c == '-')
    return '+';
  return '-';
}

int main() {
  ifstream fin("input.in");
  ofstream fout("output.out");
  fin >> T;

  int i, t, j, res;
  for (t = 1; t <= T; t++) {
    fout << "Case #" << t << ": ";
    fin >> s >> K;

    int N = s.length();
    res = 0;
    for (i = 0; i + K - 1 < N; i++) {
      if (s[i] == '-') {
        for (j = i; j < i + K; j++)
          s[j] = flip(s[j]);

        res++;
      }
    }

    bool ans = 1;
    for (i = 0; i < N; i++)
      if (s[i] == '-')
        ans = 0;

    if (ans)
      fout << res << "\n";
    else
      fout << "IMPOSSIBLE\n";
  }
  return 0;
}
