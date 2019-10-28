#include <bits/stdc++.h>
using namespace std;

ifstream fin("B-small-attempt1.in");
ofstream fout("B-small1.out");

void solve() {
  int n, r, o, y, g, b, v;
  fin >> n >> r >> o >> y >> g >> b >> v;
  int res[2000] = {};
  int cs[] = {r, y, b};
  for (int i = 0; i < n; i++) {
    int mxi = 0, mxamt = -1;
    for (int j = 0; j < 3; j++) {
      if (i > 0 && res[i - 1] == j)
        continue;
      if (cs[j] > mxamt || (cs[j] == mxamt && j == res[0]))
        mxi = j, mxamt = cs[j];
    }
    if (mxamt <= 0 || (i == n - 1 && mxi == res[0])) {
      fout << "IMPOSSIBLE\n";
      return;
    }
    cs[mxi]--, res[i] = mxi;
  }
  string conv = "RYB";
  for (int i = 0; i < n; i++)
    fout << conv[res[i]];
  fout << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int t;
  fin >> t;
  for (int i = 0; i < t; i++)
    fout << "Case #" << i + 1 << ": ", solve();
}
