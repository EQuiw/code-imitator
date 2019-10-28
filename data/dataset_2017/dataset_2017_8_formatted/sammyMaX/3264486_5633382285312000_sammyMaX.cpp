#include <bits/stdc++.h>
using namespace std;

ifstream fin("B-small3.in");
ofstream fout("B-small3.out");

string solves(string s, char prev) {
  if (s.size() == 0)
    return "";
  char minc = '9';
  for (char c : s)
    minc = min(minc, c);
  if (s[0] > minc) {
    if (s.size() > 1 && s[1] > s[0]) {
      return s[0] + solves(s.substr(1), s[0]);
    } else {
      string res = "";
      if (s[0] > minc && s[0] > '1')
        res += (char)(s[0] - 1);
      for (int i = 1; i < s.size(); i++)
        res += '9';
      return res;
    }
  }
  return minc + solves(s.substr(1), minc);
}

void solve() {
  string s;
  fin >> s;
  fout << solves(s, '0') << '\n';
}

int main() {
  int t;
  fin >> t;
  for (int i = 0; i < t; i++)
    fout << "Case #" << i + 1 << ": ", solve();
}
