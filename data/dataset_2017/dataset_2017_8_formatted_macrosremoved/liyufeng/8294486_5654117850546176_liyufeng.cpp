#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int T;
int a[6]; // R O Y G B V
int b[3] = {2, 3, 4};
int c[3] = {0, 4, 5};
int d[3] = {0, 1, 2};
int s[6] = {'R', 'O', 'Y', 'G', 'B', 'V'};

pair<int, int> p[6];
int rk[6];

int main() {
  freopen("B-small-attempt2.in", "r", stdin);
  freopen("B-small-attempt2.txt", "w", stdout);
  int cas = 0;

  cin >> T;
  while (T--) {
    int pre = -1;
    int n = 0;
    cin >> n;
    for (int i = 0; i < 6; i++) {
      scanf("%d", a + i);
      p[i].first = -a[i];
      p[i].second = i;
      // n += a[i];
    }
    sort(p, p + 6);
    for (int i = 0; i < 6; i++) {
      rk[p[i].second] = i;
      // cout << p[i].second << " " << i << endl;
    }
    bool flag = true;
    string ans = "";
    while (n > 0) {
      int mx = 0;
      int mxid = -1;
      if (pre == -1) {
        for (int i = 0; i < 6; i++) {
          if (a[i] > mx || (a[i] == mx && rk[i] < rk[mxid]))
            mxid = i, mx = a[i];
        }
      } else if (pre == 0) {
        for (int i = 0; i < 3; i++) {
          if (a[b[i]] > mx ||
              (mxid >= 0 && a[b[i]] == mx && rk[b[i]] < rk[mxid]))
            mxid = b[i], mx = a[b[i]];
        }
      } else if (pre == 1) {
        mx = a[4];
        mxid = 4;
      } else if (pre == 2) {
        for (int i = 0; i < 3; i++) {
          if (a[c[i]] > mx ||
              (mxid >= 0 && a[c[i]] == mx && rk[c[i]] < rk[mxid]))
            mxid = c[i], mx = a[c[i]];
        }
      } else if (pre == 3) {
        mx = a[0];
        mxid = 0;
      } else if (pre == 4) {
        for (int i = 0; i < 3; i++) {
          if (a[d[i]] > mx ||
              (mxid >= 0 && a[d[i]] == mx && rk[d[i]] < rk[mxid]))
            mxid = d[i], mx = a[d[i]];
        }
      } else if (pre == 5) {
        mx = a[2];
        mxid = 2;
      }
      if (mx == 0 || mxid < 0) {
        flag = false;
        break;
      }
      n--;
      a[mxid]--;
      pre = mxid;
      ans += s[mxid];
      // cout << a[0] << " " << a[2] << " " << a[4] << endl;
      // cout << flag << " " << ans << endl;
    }
    n = ans.length();
    // cout << flag << " " << ans << endl;
    if (ans[0] == 'R') {
      bool f = false;
      for (int i = 0; i < 3; i++) {
        if (ans[n - 1] == s[b[i]])
          f = true;
      }
      flag &= f;
    }
    //	cout << flag << endl;
    if (ans[0] == 'Y') {
      bool f = false;
      for (int i = 0; i < 3; i++) {
        if (ans[n - 1] == s[c[i]])
          f = true;
      }
      flag &= f;
    }
    //	cout << flag << endl;
    if (ans[0] == 'B') {
      bool f = false;
      for (int i = 0; i < 3; i++) {
        if (ans[n - 1] == s[d[i]])
          f = true;
      }
      flag &= f;
    }
    //	cout << flag << endl;
    if (ans[0] == 'O' && ans[n - 1] != 'B')
      flag = false;
    if (ans[0] == 'V' && ans[n - 1] != 'Y')
      flag = false;
    if (ans[0] == 'G' && ans[n - 1] != 'R')
      flag = false;
    printf("Case #%d: ", ++cas);
    if (!flag)
      cout << "IMPOSSIBLE" << endl;
    else
      cout << ans << endl;
  }
  return 0;
}
