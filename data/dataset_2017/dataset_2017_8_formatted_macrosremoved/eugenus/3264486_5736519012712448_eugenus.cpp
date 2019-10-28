#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef pair<int, int> par;
typedef long long int tint;
map<char, char> inv;

int main() {
  freopen("test.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  inv['-'] = '+';
  inv['+'] = '-';
  int t, k;
  string s;

  cin >> t;

  for (int caso = (1); caso < (t + 1); caso++) {
    cin >> s >> k;
    int l = s.size();

    int ans = 0;
    for (int i = 0; i < (l + 1 - k); i++) {
      if (s[i] == '-') {
        for (int j = (i); j < (i + k); j++)
          s[j] = inv[s[j]];
        ans++;
      }
    }
    bool check = true;
    for (int i = 0; i < (l); i++) {
      check = check and s[i] == '+';
    }
    cout << "Case #" << caso << ": ";
    if (check)
      cout << ans << endl;
    else
      cout << "IMPOSSIBLE" << endl;
  }

  return 0;
}
