

#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;

bool func(string &cur, string &orig, long long index) {
  long long n = orig.length();
  if (index >= n)
    return true;
  for (char i = '9'; i >= cur[index - 1]; --i) {
    cur[index] = i;
    if (cur.substr(0, index + 1) > orig.substr(0, index + 1))
      continue;
    bool tmp = func(cur, orig, index + 1);
    if (tmp)
      return true;
  }
  cur[index] = orig[index];
  return false;
}

int main() {

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  ;
  freopen("inp.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  long long t;
  cin >> t;
  cin.ignore(256, '\n');
  for (long long ccr = 1; ccr <= t; ++ccr) {
    string inp, orig;
    cin >> inp;
    inp = "0" + inp;
    orig = inp;

    bool poss = func(inp, orig, 1);
    long long n = inp.length();
    if (poss) {
      long long i = 0;
      while (i < n - 1 && inp[i] == '0')
        ++i;
      inp = inp.substr(i);
      cout << "Case #" << ccr << ": " << inp << "\n";
    }
  }

  return 0;
}
