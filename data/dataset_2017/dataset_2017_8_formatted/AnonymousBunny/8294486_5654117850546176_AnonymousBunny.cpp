#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define mp make_pair
#define F first
#define S second
const int mod = 1e9 + 7;
#define maxn 1020
#define pii pair<int, int>
#define mp make_pair
#define F first
#define S second

#define inf 100000000000000LL
#define dist _ist
int a[maxn][maxn];

int e[maxn], s[maxn];

void solve(int ind) {
  int n, r, o, y, g, b, V;
  cin >> n >> r >> o >> y >> g >> b >> V;
  assert(r + o + y + g + b + V == n);
  vector<pair<int, char>> v;
  v.push_back(mp(r, 'r'));
  v.push_back(mp(y, 'y'));
  v.push_back(mp(b, 'b'));
  sort(v.begin(), v.end());
  if (v[2].F > v[0].F + v[1].F) {
    cout << "Case #" << ind << ": IMPOSSIBLE" << endl;
    return;
  }
  string s = "";
  while (v[1].F) {
    s += v[2].S;
    s += v[1].S;
    v[1].F--;
    v[2].F--;
  }
  while (v[2].F) {
    s += v[2].S;
    s += v[0].S;
    v[0].F--;
    v[2].F--;
  }
  cout << "Case #" << ind << ": ";
  for (int i = 0; i < s.size(); i++) {
    if (s[i] != v[1].S)
      cout << s[i];
    else {
      if (v[0].F) {
        cout << s[i];
        cout << v[0].S;
        v[0].F--;
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