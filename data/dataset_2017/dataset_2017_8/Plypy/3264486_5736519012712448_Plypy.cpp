#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
bool flag[MAXN];

int main()
{
  int T;
  cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    memset(flag, 0, sizeof(flag));
    string str;
    int k;
    cin >> str >> k;
    int ans = 0;
    int flip = 0;
    bool impossible = false;
    for (int i = 0; i < str.size(); ++i) {
      if (i - k >= 0) {
        if (flag[i-k]) flip ^= 1;
      }
      int happy = (str[i] == '+' ? 1 : 0) ^ flip;
      if (!happy) {
        if (i + k > str.size()) {
          impossible = true;
          break;
        }
        ++ans;
        flag[i] = 1;
        flip ^= 1;
      }
    }
    if (impossible)
      printf("Case #%d: IMPOSSIBLE\n", cas);
    else
      printf("Case #%d: %d\n", cas, ans);
  }
}
