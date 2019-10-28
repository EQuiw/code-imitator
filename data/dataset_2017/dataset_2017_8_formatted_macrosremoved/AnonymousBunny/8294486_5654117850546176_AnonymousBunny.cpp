#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
int a[1020][1020];

int e[1020], s[1020];

void solve(int ind) {
  int n, r, o, y, g, b, V;
  cin >> n >> r >> o >> y >> g >> b >> V;
  assert(r + o + y + g + b + V == n);
  vector<pair<int, char>> v;
  v.push_back(make_pair(r, 'r'));
  v.push_back(make_pair(y, 'y'));
  v.push_back(make_pair(b, 'b'));
  sort(v.begin(), v.end());
  if (v[2].first > v[0].first + v[1].first) {
    cout << "Case #" << ind << ": IMPOSSIBLE" << endl;
    return;
  }
  string s = "";
  while (v[1].first) {
    s += v[2].second;
    s += v[1].second;
    v[1].first--;
    v[2].first--;
  }
  while (v[2].first) {
    s += v[2].second;
    s += v[0].second;
    v[0].first--;
    v[2].first--;
  }
  cout << "Case #" << ind << ": ";
  for (int i = 0; i < s.size(); i++) {
    if (s[i] != v[1].second)
      cout << s[i];
    else {
      if (v[0].first) {
        cout << s[i];
        cout << v[0].second;
        v[0].first--;
      } else {
        cout << s[i];
      }
    }
  }
  cout << endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++)
    solve(i);
  return 0;
}
