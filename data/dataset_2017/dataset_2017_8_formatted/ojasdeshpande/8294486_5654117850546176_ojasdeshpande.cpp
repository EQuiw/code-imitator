#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int t = 1; t <= tt; t++) {
    cout << "Case #" << t << ": ";
    int a[6];
    int n;
    cin >> n;
    for (int i = 0; i < 6; i++)
      cin >> a[i];
    int b[6];
    for (int i = 0; i < 6; i++)
      b[i] = a[i];
    int v[n];
    for (int i = 0; i < n; i++)
      v[i] = -1;
    int flag = 0;
    int cur = 0;
    int last = -1;
    int first = -1;
    if (a[1] != 0) {
      if ((a[4] < a[1]) || ((a[4] == a[1]) && (a[4] + a[1] != n))) {
        flag = 1;
        cout << "IMPOSSIBLE\n";
        continue;
      }
      v[0] = 4;
      a[4]--;
      cur++;
      for (int i = 0; i < a[1]; i++) {
        v[cur++] = 1;
        if (cur != n)
          v[cur++] = 4;
      }
      a[4] -= a[1];
      a[1] = 0;
      last = 4;
      first = 4;
    }
    if (a[3] != 0) {
      if (a[0] < a[3] || (a[0] == a[3] && (a[0] + a[3] != n))) {
        flag = 1;
        cout << "IMPOSSIBLE\n";
        continue;
      }
      v[cur++] = 0;
      a[0]--;
      for (int i = 0; i < a[3]; i++) {
        v[cur++] = 3;
        if (cur != n)
          v[cur++] = 0;
      }
      a[0] -= a[3];
      a[3] = 0;
      last = 0;
      if (first == -1)
        first = 0;
    }
    if (a[5] != 0) {
      if (a[2] < a[5] || (a[2] == a[5] && (a[2] + a[5] != n))) {
        flag = 1;
        cout << "IMPOSSIBLE\n";
        continue;
      }
      v[cur++] = 2;
      a[2]--;
      for (int i = 0; i < a[5]; i++) {
        v[cur++] = 5;
        if (cur != n)
          v[cur++] = 2;
      }
      a[2] -= a[5];
      a[5] = 0;
      last = 2;
      if (first == -1)
        first = 2;
    }
    pair<int, pair<int, int>> r[3];
    r[0] = {a[0], {0, 0}};
    r[1] = {a[2], {0, 2}};
    r[2] = {a[4], {0, 4}};
    if (first != -1) {
      r[first / 2].second.first = 1;
    }
    flag = 0;
    while (cur != n) {
      sort(r, r + 3);
      int f = 0;
      for (int i = 2; i >= 0; i--) {
        if (r[i].second.second != last) {
          if (r[i].first == 0) {
            flag = 1;
            break;
          }
          f = 1;
          r[i].first -= 1;
          // cout << r[i].second ;
          v[cur++] = r[i].second.second;
          last = r[i].second.second;
          if (first == -1) {
            r[i].second.first = 1;
            first = 1;
          }
          break;
        }
      }
      if (f == 0)
        flag = 1;
      if (flag == 1) {
        cout << "IMPOSSIBLE\n";
        break;
      }
    }
    if (flag)
      continue;
    if (v[0] == v[n - 1]) {
      cout << "IMPOSSIBLE\n";
      continue;
    }
    string s = "ROYGBV";
    int c[6];
    for (int i = 0; i < 6; i++)
      c[i] = 0;
    for (int i = 0; i < n; i++) {
      c[v[i]]++;
      cout << s[v[i]];
    }
    for (int i = 0; i < 6; i++)
      assert(b[i] == c[i]);
    cout << "\n";
  }
  return 0;
}