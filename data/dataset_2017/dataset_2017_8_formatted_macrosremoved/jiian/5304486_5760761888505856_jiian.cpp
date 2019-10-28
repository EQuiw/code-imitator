#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int T, cas;

string convert(string s) {
  int p, i;
  for (p = 0, i = 0; s[i]; i++) {
    if (s[i] != '?')
      while (p <= i)
        s[p++] = s[i];
  }
  if (!p)
    return s;
  while (s[--i] == '?')
    s[i] = s[p - 1];
  return s;
}

int main() {
  freopen("123.in", "r", stdin);
  freopen("123.out", "w", stdout);
  cin >> T;
  while (T--) {
    vector<string> a;
    int n, m;
    cin >> n >> m;
    int p = 0, i;
    for (i = 0; i < n; i++) {
      string s;
      cin >> s;
      s = convert(s);
      a.push_back(s);
      if (s[0] != '?')
        while (p <= i)
          a[p++] = a[i];
    }
    while (a[--i][0] == '?')
      a[i] = a[p - 1];
    printf("Case #%d:\n", ++cas);
    for (auto s : a)
      printf("%s\n", s.c_str());
  }
  return 0;
}
