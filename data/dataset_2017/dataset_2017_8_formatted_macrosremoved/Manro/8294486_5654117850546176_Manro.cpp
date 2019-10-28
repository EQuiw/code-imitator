#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> Matrix;

const int INF = 1e9 + 7;
const double PI = acos(-1);
const double EPS = 1e-9;

const int N = 1e2;

enum { R, O, Y, G, B, V };
vector<char> res;

bool solve(int r, int y, int b) {
  int mx = max(r, max(y, b));
  //	D(mx);
  if (!r && !y && !b) {
    return res.back() != res[0];
  }
  if (r && mx == r && res.back() != 'R') {
    res.push_back('R');
    if (solve(r - 1, y, b))
      return true;
    res.pop_back();
  }
  if (y && mx == y && res.back() != 'Y') {
    res.push_back('Y');
    if (solve(r, y - 1, b))
      return true;
    res.pop_back();
  }
  if (b && mx == b && res.back() != 'B') {
    res.push_back('B');
    if (solve(r, y, b - 1))
      return true;
    res.pop_back();
  }
  if (r && mx != r && res.back() != 'R') {
    res.push_back('R');
    if (solve(r - 1, y, b))
      return true;
    res.pop_back();
  }
  if (y && mx != y && res.back() != 'Y') {
    res.push_back('Y');
    if (solve(r, y - 1, b))
      return true;
    res.pop_back();
  }
  if (b && mx != b && res.back() != 'B') {
    res.push_back('B');
    if (solve(r, y, b - 1))
      return true;
    res.pop_back();
  }
  return false;
}

int main() {
  int t, n, r, o, y, g, b, v;
  cin >> t;

  for (int caseNr = (1); caseNr < (t + 1); ++caseNr) {
    cin >> n >> r >> o >> y >> g >> b >> v;
    cout << "Case #" << caseNr << ": ";
    int mx = max(r, max(y, b));
    if (mx > r + y + b - mx) {
      cout << "IMPOSSIBLE" << endl;
      continue;
    }
    res.clear();
    if (mx == r) {
      res.push_back('R');
      --r;
    } else if (mx == y) {
      res.push_back('Y');
      --y;
    } else if (mx == b) {
      res.push_back('B');
      --b;
    }
    if (!solve(r, y, b)) {
      cout << "IMPOSSIBLE" << endl;
      continue;
    } else {
      for (char c : res)
        cout << c;
      cout << endl;
    }
  }
  return 0;
}
