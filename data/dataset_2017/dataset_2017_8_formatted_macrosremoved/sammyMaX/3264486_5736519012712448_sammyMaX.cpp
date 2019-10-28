#include <bits/stdc++.h>
using namespace std;

ifstream fin("A-small-attempt1.in");
ofstream fout("A-small1.out");

void solve() {
  string s;
  int fsize;
  fin >> s >> fsize;

  int flips[1005] = {}, res = 0, i = 0;
  for (char c : s) {
    if (i >= fsize)
      res -= flips[i - fsize];
    int now = (c == '+');
    if (i <= s.size() - fsize && (now + res) % 2 == 0)
      flips[i] = 1;
    res += flips[i];
    i++;
    if ((now + res) % 2 == 0) {
      fout << "IMPOSSIBLE\n";
      return;
    }
  }
  res = 0;
  for (int a : flips)
    res += a;
  fout << res << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int t;
  fin >> t;
  for (int i = 0; i < t; i++)
    fout << "Case #" << i + 1 << ": ", solve();
}
