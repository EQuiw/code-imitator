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

LL T, N, K, ans_min, ans_max;

void get_ans(LL l, LL r, LL K) {
  if (K == 1) {
    ans_min = (l + r) / 2 - l;
    ans_max = r - (l + r) / 2;
    return;
  }

  if ((l + r) % 2 == 0)
    get_ans(l, (l + r) / 2, K / 2);
  else {
    if ((K - 1) % 2 == 0)
      get_ans(l, (l + r) / 2, (K - 1) / 2);
    else
      get_ans((l + r) / 2, r, K / 2);
  }
}

int main() {
  ifstream fin("input.in");
  ofstream fout("output.out");
  fin >> T;

  int t;
  for (t = 1; t <= T; t++) {
    fout << "Case #" << t << ": ";
    fin >> N >> K;
    get_ans(0, N + 1, K);
    fout << ans_max - 1 << " " << ans_min - 1 << "\n";
  }
  return 0;
}
