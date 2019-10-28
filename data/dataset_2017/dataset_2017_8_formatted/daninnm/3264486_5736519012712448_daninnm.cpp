#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int t, n, k;
char s[1024];
int main() {
  freopen("in.in", "r", stdin);
  freopen("out.out", "w", stdout);
  cin >> t;
  int retarded = 1;
  while (t--) {
    int ans = 0;
    cin >> s >> k;
    n = strlen(s);
    for (int i = 0; i < n - k + 1; ++i) {
      if (s[i] == '-') {
        ++ans;
        for (int j = i; j < i + k; ++j) {
          if (s[j] == '-') {
            s[j] = '+';
          } else {
            s[j] = '-';
          }
        }
      }
    }
    for (int i = n - k + 1; i < n; ++i) {
      if (s[i] == '-')
        ans = -1;
    }
    cout << "Case #" << retarded << ": ";
    if (ans == -1)
      cout << "IMPOSSIBLE";
    else {
      cout << ans;
    }
    cout << endl;
    retarded++;
  }
  return 0;
}
