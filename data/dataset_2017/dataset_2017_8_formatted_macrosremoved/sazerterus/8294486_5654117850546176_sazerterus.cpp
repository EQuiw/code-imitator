#include <bits/stdc++.h>

using namespace std;
string ok(int n) {
  if (n == 1)
    return "R";
  if (n == 2)
    return "B";
  return "Y";
}
int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t;
  cin >> t;
  int index = 1;
  while (t--) {
    int n, r, o, y, g, b, v;
    cin >> n >> r >> o >> y >> g >> b >> v;
    int ma = max(r, max(y, b));
    if (2 * ma > r + y + b) {
      cout << "Case #" << index++ << ": "
           << "IMPOSSIBLE" << endl;
      continue;
    }
    string ans = "";
    vector<pair<int, int>> V;
    V.push_back(make_pair(r, 1));
    V.push_back(make_pair(b, 2));
    V.push_back(make_pair(y, 3));
    sort(V.begin(), V.end());
    r = V[2].first;
    b = V[1].first;
    y = V[0].first;
    if (r >= b && r >= y) {
      if (b >= y) {
        int u = r - b;
        u = y - u;
        for (int i = 1; i <= u; ++i) {
          ans += "RBY";
        }
        u = b - u;
        for (int i = 1; i <= u; ++i) {
          ans += "RB";
        }
        u = r - b;
        for (int i = 1; i <= u; ++i) {
          ans += "RY";
        }
      } else {
        int u = r - y;
        u = b - u;
        for (int i = 1; i <= u; ++i) {
          ans += "RYB";
        }
        u = y - u;
        for (int i = 1; i <= u; ++i) {
          ans += "RY";
        }
        u = r - y;
        for (int i = 1; i <= u; ++i) {
          ans += "RB";
        }
      }
    }
    string temp = "";
    for (int i = 0; i < ans.size(); ++i) {
      if (ans[i] == 'R') {
        temp += ok(V[2].second);
      } else if (ans[i] == 'B') {
        temp += ok(V[1].second);
      } else {
        temp += ok(V[0].second);
      }
    }
    cout << "Case #" << index++ << ": " << temp << endl;
  }

  return 0;
}
