#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int main() {
#ifdef _DEBUG
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int t;
  cin >> t;
  for (int tt = 0; tt < t; ++tt) {
    string str;
    cin >> str;
    int k;
    cin >> k;
    int cnt = 0;
    for (int i = 0; i + k - 1 < str.size(); ++i) {
      if (str[i] == '-') {
        cnt++;
        for (int j = i; j < i + k; ++j)
          str[j] = str[j] == '-' ? '+' : '-';
      }
    }
    bool okfl = 1;
    for (int i = 0; i < str.size(); ++i)
      if (str[i] == '-')
        okfl = 0;

    cout << "Case #" << tt + 1 << ": ";
    if (okfl) {
      cout << cnt;
    } else {
      cout << "IMPOSSIBLE";
    }
    cout << '\n';
  }
  return 0;
}
