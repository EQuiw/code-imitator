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

int N, a[110], P, cnt[10], T;
vector<int> ct;
map<vector<int>, int> mp;

int calc(int k, int r) {
  if (k == N) {
    if (r == 0)
      return 1;
    return 0;
  }

  if (mp.count(ct))
    return mp[ct];

  int i, res = 0;
  for (i = 0; i < P; i++)
    if (ct[i] < cnt[i]) {
      ct[i]++;
      res = max(res, calc(k + 1, (r + i) % P));
      ct[i]--;
    }

  if (r == 0)
    res++;
  mp[ct] = res;
  return res;
}

int main() {
  ifstream fin("input.in");
  ofstream fout("output.out");
  fin >> T;

  int i, t;
  for (t = 1; t <= T; t++) {
    cout << t << "\n";
    fout << "Case #" << t << ": ";
    fin >> N >> P;

    memset(cnt, 0, sizeof(cnt));
    for (i = 1; i <= N; i++) {
      fin >> a[i];
      cnt[a[i] % P]++;
    }

    ct.clear();
    ct.resize(P);
    mp.clear();
    fout << calc(1, 0) << "\n";
  }
  return 0;
}
