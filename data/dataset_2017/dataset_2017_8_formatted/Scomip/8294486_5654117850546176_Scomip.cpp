#include <bits/stdc++.h>

using namespace std;

string imp = "IMPOSSIBLE";

string build(char u, char c, int &iu, int &ic) {
  string ret;
  if (iu < ic)
    return imp;
  iu -= ic;
  while (ic--) {
    ret.push_back(u);
    ret.push_back(c);
  }
  return ret;
}

struct letter {
  int n;
  char c;
  bool operator<(const letter &l) const { return n > l.n; }
};

string solve() {
  int n, r, o, y, g, b, v;
  cin >> n >> r >> o >> y >> g >> b >> v;
  string a[3];
  a[0] = build('R', 'G', r, g);
  a[1] = build('Y', 'V', y, v);
  a[2] = build('B', 'O', b, o);
  for (int i = 0; i < 3; i++)
    if (a[i] == imp)
      return imp;
  int cnt = 0;
  for (int i = 0; i < 3; i++)
    cnt += a[i].length();
  if (cnt == n) {
    if (a[0].length() == n)
      return a[0];
    if (a[1].length() == n)
      return a[1];
    if (a[2].length() == n)
      return a[2];
  }
  if (a[0].length()) {
    if (!r)
      return imp;
    r--;
    cnt++;
    a[0].push_back('R');
    r++;
  }
  if (a[1].length()) {
    if (!y)
      return imp;
    y--;
    cnt++;
    a[1].push_back('Y');
    y++;
  }
  if (a[2].length()) {
    if (!b)
      return imp;
    b--;
    cnt++;
    a[2].push_back('B');
    b++;
  }
  string ans;
  letter l[3] = {{r, 'R'}, {y, 'Y'}, {b, 'B'}};
  sort(l, l + 3);
  while (l[0].n) {
    ans.push_back(l[0].c);
    l[0].n--;
    if (l[1].n == 0 && l[2].n == 0)
      return imp;
    if (l[0].n == 0)
      break;
    if (l[1].n > l[2].n) {
      ans.push_back(l[1].c);
      l[1].n--;
    } else {
      ans.push_back(l[2].c);
      l[2].n--;
    }
  }
  if (l[1].n - l[2].n > 1)
    return imp;
  while (l[1].n || l[2].n) {
    if (l[1].n > l[2].n) {
      ans.push_back(l[1].c);
      l[1].n--;
    } else {
      ans.push_back(l[2].c);
      l[2].n--;
    }
  }
  string ret;
  bool f1 = false, f2 = false, f3 = false;
  if (a[0].length() == 0)
    f1 = true;
  if (a[1].length() == 0)
    f2 = true;
  if (a[2].length() == 0)
    f3 = true;
  for (char c : ans)
    if (c == 'R' && !f1)
      ret += a[0], f1 = true;
    else if (c == 'Y' && !f2)
      ret += a[1], f2 = true;
    else if (c == 'B' && !f3)
      ret += a[2], f3 = true;
    else
      ret.push_back(c);
  return ret;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case #" << i << ": ";
    cout << solve() << endl;
  }

  return 0;
}
