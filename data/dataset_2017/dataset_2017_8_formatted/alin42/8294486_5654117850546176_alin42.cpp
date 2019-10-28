#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string simple(int r, int yy, int b) {
  vector<pair<int, string>> v;
  v.push_back({r, "R"});
  v.push_back({yy, "Y"});
  v.push_back({b, "B"});
  sort(v.begin(), v.end());
  string x = v[0].second;
  string y = v[1].second;
  string z = v[2].second;
  int t1 = v[0].first, t2 = v[1].first, t3 = v[2].first;
  string s = "";
  if (t1 == 0) {
    if (t3 - t2 > 1)
      return "IMPOSSIBLE";
    if (t3 - t2 == 1)
      s += z;
    for (int i = 0; i < t2; i++)
      s += y + z;
    return s;
  }
  for (int i = 0; (t3 > t2) && (t1 > 0); i++) {
    s += z + x;
    t1--;
    t3--;
  }
  for (int i = 0; i < t1; i++) {
    s += y + z + x;
    t2--, t3--;
  }
  if (t3 > t2 + 1)
    return "IMPOSSIBLE";
  for (int i = 0; i < t2; i++)
    s += z + y;
  if (t3 == t2 + 1)
    s += z;
  return s;
}
string solve(int r, int o, int y, int g, int b, int v) {
  string s = "";
  int n = r + o + y + g + b + v;
  if (r + g == n) {
    if (r == g) {
      for (int i = 0; i < r; i++)
        s += "RG";
      return s;
    }
    return "IMPOSSIBLE";
  }
  if (b + o == n) {
    if (b == o) {
      for (int i = 0; i < o; i++)
        s += "BO";
      return s;
    }
    return "IMPOSSIBLE";
  }
  if (y + v == n) {
    if (y == v) {
      for (int i = 0; i < v; i++)
        s += "YV";
      return s;
    }
    return "IMPOSSIBLE";
  }
  if ((g != 0) && (g + 1 > r))
    return "IMPOSSIBLE";
  if ((v != 0) && (v + 1 > y))
    return "IMPOSSIBLE";
  if ((o != 0) && (o + 1 > b))
    return "IMPOSSIBLE";

  if (r == 0) {
    s = simple(r, y - (v + 1), b - (o + 1));
    if (s.size()) {
      if (s[0] == 'I')
        return s;
      if (s[0] == s[s.size() - 1])
        return "IMPOSSIBLE";
    }
    s += 'B';
    for (int i = 0; i < o; i++)
      s += "OB";
    s += 'Y';
    for (int i = 0; i < v; i++)
      s += "VY";
    return s;
  }
  if (y == 0) {
    s = simple(r - (g + 1), y, b - (o + 1));
    if (s.size()) {
      if (s[0] == 'I')
        return s;
      if (s[0] == s[s.size() - 1])
        return "IMPOSSIBLE";
    }
    s += 'B';
    for (int i = 0; i < o; i++)
      s += "OB";
    s += 'R';
    for (int i = 0; i < v; i++)
      s += "GR";
    return s;
  }
  if (b == 0) {
    s = simple(r - (g + 1), y - (v + 1), b);
    if (s.size()) {
      if (s[0] == 'I')
        return s;
      if (s[0] == s[s.size() - 1])
        return "IMPOSSIBLE";
    }
    s += 'R';
    for (int i = 0; i < g; i++)
      s += "GR";
    s += 'Y';
    for (int i = 0; i < v; i++)
      s += "VY";
    return s;
  }
  // now we're equiped with all three.
  string part = simple(r - (g + 1), y - (v + 1), b - (o + 1));
  if (part[0] == 'I')
    return part;
  s += "R";
  for (int i = 0; i < g; i++)
    s += "GR";
  if (part[0] == 'Y') {
    if (part[part.size() - 1] == 'B') {
      reverse(part.begin(), part.end());
      s += part;
      reverse(part.begin(), part.end());
    } else
      s += part;
  }
  s += "B";
  for (int i = 0; i < o; i++)
    s += "OB";
  if (part[0] == 'R') {
    if (part[part.size() - 1] == 'Y') {
      reverse(part.begin(), part.end());
      s += part;
      reverse(part.begin(), part.end());
    } else
      s += part;
  }
  s += "Y";
  for (int i = 0; i < v; i++)
    s += "VY";
  if (part[0] == 'B') {
    if (part[part.size() - 1] == 'R') {
      reverse(part.begin(), part.end());
      s += part;
      reverse(part.begin(), part.end());
    } else
      s += part;
  }
  return s;
}
bool check(string s, int n, int r, int o, int y, int g, int b, int v) {
  if (s[0] == 'I')
    return true;
  if (s.size() != n)
    return 0;
  int i = 0, j = 0, k = 0;
  for (int x = 0; x < n; x++) {
    if (s[x] == 'R')
      i++;
    if (s[x] == 'Y')
      j++;
    if (s[x] == 'B')
      k++;
  }
  if (i != r)
    return false;
  if (j != y)
    return false;
  if (k != b)
    return false;
  return true;
}
int main() {
  ios::sync_with_stdio(0);
  freopen("readable.txt", "w", stdout);
  int t;
  cin >> t;
  for (int ca = 1; ca <= t; ca++) {
    int n, r, o, y, g, b, v;
    cin >> n >> r >> o >> y >> g >> b >> v;
    string s = solve(r, o, y, g, b, v);
    cout << "Case #" << ca << ": " << s << endl;
    if (check(s, n, r, o, y, g, b, v) == 0)
      cout << "AHH"
           << " " << r << " " << o << " " << y << " " << g << " " << b << " "
           << v << endl;
  }
  return 0;
}

// g++ -std=c++11 -O2 -Wfatal-errors -Im -Wall -Wextra -o "output.txt"
// "code.cpp"