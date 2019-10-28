#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

ll t, r, c;
string cake[30];

const string EMPTY = "!@#$";

inline void solve() {
  cin >> r >> c;
  for (int i = 0; i < r; i++)
    cin >> cake[i];

  vector<vector<char>> v(r, vector<char>(c));

  for (int i = 0; i < r; i++) {
    char last = 0;
    for (int j = c - 1; j >= 0; j--) {
      if (cake[i][j] != '?')
        last = cake[i][j];
      else if (last != 0)
        cake[i][j] = last;
    }
    last = 0;
    for (int j = 0; j < c; j++) {
      if (cake[i][j] != '?')
        last = cake[i][j];
      else if (last != 0)
        cake[i][j] = last;
    }
  }

  // cerr << "SETTED ROWS" << endl;

  vector<bool> is(r);
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (cake[i][j] != '?') {
        is[i] = true;
        break;
      }
    }
  }

  // cerr << "CHECKED ROWS" << endl;

  string last = EMPTY;
  for (int i = 0; i < r; i++) {
    if (is[i])
      last = cake[i];
    else if (last != EMPTY)
      cake[i] = last;
  }
  last = EMPTY;
  for (int i = r - 1; i >= 0; i--) {
    if (is[i])
      last = cake[i];
    else if (last != EMPTY)
      cake[i] = last;
  }

  // cerr << "DONE!" << endl;

  for (int i = 0; i < r; i++)
    cout << cake[i] << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cout << "Case #" << i << ":\n";
    solve();
  }
}
