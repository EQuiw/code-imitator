#include <bits/stdc++.h>

using namespace std;

#define ll long long

char chs[] = {'R', 'O', 'Y', 'G', 'B', 'V'};

map<char, int> mp;

struct Color {
  int val;
  char col;
  bool operator<(const Color &o) const {
    return (val * 10 + mp[col]) > (o.val * 10 + mp[o.col]);
  }
} color[6];

char ans[1005];

int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-small-attempt0.out", "w", stdout);

  mp['R'] = 2;
  mp['Y'] = 2;
  mp['B'] = 2;

  mp['O'] = 1;
  mp['G'] = 1;
  mp['V'] = 1;

  int t;
  cin >> t;
  int cas = 0;

  while (t--) {
    cas++;
    memset(ans, 0, sizeof(ans));

    int n;
    cin >> n;

    for (int i = 0; i < 6; i++) {
      cin >> color[i].val;
      color[i].col = chs[i];
    }

    sort(color, color + 6);

    if (color[0].val > (n / 2)) {
      printf("Case #%d: IMPOSSIBLE\n", cas);
      continue;
    }

    int pos = 0;
    while (color[0].val--) {
      ans[pos] = color[0].col;
      pos += 2;
    }

    pos--;
    for (; pos < n; pos += 2) {
      if (color[1].val) {
        ans[pos] = color[1].col;
        color[1].val--;
      }
    }

    for (int i = 0; i < n; i++) {
      if (ans[i] == 0) {
        if (color[1].val > 0) {
          color[1].val--;
          ans[i] = color[1].col;
        } else {
          ans[i] = color[2].col;
        }
      }
    }

    ans[n] = '\0';

    printf("Case #%d: %s\n", cas, ans);
  }
  return 0;
}
