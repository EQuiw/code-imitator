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

const int N = 1e6 + 5;

set<int> X[256];
set<int> Y[256];

int t, rows, cols;

bool isValid(vector<string> &grid) {
  /* cout << ">> " << #x << " = >" << x << "<" << endl*/;
  set<int> X[256], Y[256];
  for (int r = (0); r < (rows); ++r) {
    for (int c = (0); c < (cols); ++c) {
      X[grid[r][c]].insert(c);
      Y[grid[r][c]].insert(r);
    }
  }
  for (int i = ('A'); i < ('Z' + 1); ++i) {
    if (!X[i].empty()) {
      for (int r = (*Y[i].begin()); r < (*Y[i].rbegin() + 1); ++r)
        for (int c = (*X[i].begin()); c < (*X[i].rbegin() + 1); ++c)
          if (grid[r][c] != i) {
            /* cout << ">> " << #x << " = >" << x << "<" << endl*/;
            return false;
          }
    }
  }
  /* cout << ">> " << #x << " = >" << x << "<" << endl*/;
  return true;
}

bool solve(vector<string> &grid, set<char> &symbols) {
  int r, c;
  for (r = 0; r < rows; ++r)
    for (c = 0; c < cols; ++c)
      if (grid[r][c] == '?')
        goto hell;
hell:;
  /* cout << ">> " << #x << " = >" << x << "<" << endl*/;
  /* cout << ">> " << #x << " = >" << x << "<" << endl*/;
  if (r == rows)
    return isValid(grid);
  for (char symbol : symbols) {
    /* cout << ">> " << #x << " = >" << x << "<" << endl*/;
    grid[r][c] = symbol;
    if (solve(grid, symbols))
      return true;
  }
  grid[r][c] = '?';
  return false;
}

int main() {
  cin >> t;

  for (int caseNr = (1); caseNr < (t + 1); ++caseNr) {
    cin >> rows >> cols;
    for (int i = ('A'); i < ('Z' + 1); ++i) {
      X[i].clear();
      Y[i].clear();
    }
    vector<string> grid(rows);
    set<char> symbols;
    for (int r = (0); r < (rows); ++r) {
      cin >> grid[r];
      for (int c = (0); c < (cols); ++c) {
        symbols.insert(grid[r][c]);
        X[grid[r][c]].insert(c);
        Y[grid[r][c]].insert(r);
      }
    }
    for (int i = ('A'); i < ('Z' + 1); ++i) {
      if (!X[i].empty()) {
        for (int r = (*Y[i].begin()); r < (*Y[i].rbegin() + 1); ++r)
          for (int c = (*X[i].begin()); c < (*X[i].rbegin() + 1); ++c)
            grid[r][c] = i;
      }
    }
    symbols.erase('?');
    solve(grid, symbols);
    cout << "Case #" << caseNr << ":" << endl;
    for (int r = (0); r < (rows); ++r)
      cout << grid[r] << endl;
  }
  return 0;
}
