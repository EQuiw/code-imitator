#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e4 + 5;
const double eps = 1e-3;
const int INF = 1e9;

priority_queue<pair<int, int>> q;
int tmp[1010];
string s = "RYB";
int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-small-attempt0.out", "w", stdout);
  int t, ca = 1;
  scanf("%d", &t);
  while (t--) {
    printf("Case #%d: ", ca++);
    int n, r, o, y, g, b, v;
    scanf("%d%d%d%d%d%d%d", &n, &r, &o, &y, &g, &b, &v);
    if (b <= o - 1 || r <= g - 1 || y <= v - 1) {
      puts("IMPOSSIBLE");
      continue;
    }
    string anso = "";
    while (o) {
      o--, b--;
      n -= 2;
      anso += "BO";
    }
    string ansg = "";
    while (g) {
      g--, r--;
      n -= 2;
      ansg += "RG";
    }
    string ansv = "";
    while (v) {
      v--, y--;
      n -= 2;
      ansv += "YV";
    }
    string ans = "";
    if (anso != "" && ansg != "" && ansv != "") {
      if (r < 1 || y < 1 || b < 1) {
        puts("IMPOSSIBLE");
        continue;
      }
      ans = anso + "B" + ansg + "R" + ansv + "Y";
    } else if (anso != "" && ansg != "") {
      if (r < 1 || b < 1) {
        puts("IMPOSSIBLE");
        continue;
      }
      ans = anso + "B" + ansg + "R";
    } else if (anso != "" && ansv != "") {
      if (y < 1 || b < 1) {
        puts("IMPOSSIBLE");
        continue;
      }
      ans += anso + "B" + ansv + "Y";
    } else if (ansg != "" && ansv != "") {
      if (r < 1 || y < 1) {
        puts("IMPOSSIBLE");
        continue;
      }
      ans += ansg + "R" + ansv + "Y";
    } else
      ans = anso + ansg + ansv;
    if (n == 0)
      cout << ans << endl;
    else {
      while (!q.empty())
        q.pop();
      if (r)
        q.push({r, 1});
      if (y)
        q.push({y, 2});
      if (b)
        q.push({b, 3});
      int f = 1, cnt = 1;
      while (!q.empty() && f) {
        pair<int, int> a = q.top(), c;
        q.pop();
        a.first--;
        if (a.second == tmp[cnt - 1])
          f = 0;
        tmp[cnt++] = a.second;
        if (!q.empty()) {
          c = q.top();
          q.pop();
          c.first--;
          tmp[cnt++] = c.second;
        }
        if (a.first)
          q.push(a);
        if (c.first)
          q.push(c);
      }
      if (f && tmp[1] == tmp[n]) {
        swap(tmp[n - 1], tmp[n]);
        if (tmp[n - 2] == tmp[n - 1] || tmp[1] == tmp[n])
          f = 0;
      }
      if (f)
        for (int i = 1; i <= n; i++)
          cout << s[tmp[i] - 1];
      else
        printf("IMPOSSIBLE");
      puts("");
    }
  }
  return 0;
}
