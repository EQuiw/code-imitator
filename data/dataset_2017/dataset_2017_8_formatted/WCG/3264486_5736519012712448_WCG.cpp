#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  int tt;

  cin >> tt;

  for (int t = 1; t <= tt; ++t) {
    string s;
    int k, res = 0;
    cin >> s >> k;
    for (int i = 0; i + k <= s.size(); ++i) {
      if (s[i] == '-') {
        for (int j = 0; j < k; ++j)
          s[i + j] = (s[i + j] == '-') ? '+' : '-';
        res++;
      }
    }
    for (int i = 0; i < s.size(); ++i)
      if (s[i] == '-')
        res = -1;

    cout << "Case #" << t << ": ";
    if (res == -1)
      cout << "IMPOSSIBLE" << endl;
    else
      cout << res << endl;
  }

  return 0;
}
