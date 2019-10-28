#include <bits/stdc++.h>
#define ff first
#define ss second
#define ALL(x) (x).begin(), (x).end()
#define D(x) // cout << ">> " << #x << " = >" << x << "<" << endl
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define PB push_back
#define R1(a) scanf("%d", &a)
#define R2(a, b) scanf("%d%d", &a, &b)
#define R3(a, b, c) scanf("%d%d%d", &a, &b, &c)
#define P(cond)                                                                \
  do {                                                                         \
    if (!(cond)) {                                                             \
      puts("Nespravny vstup.");                                                \
      return 1;                                                                \
    }                                                                          \
  } while (0)
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
  D("isValid");
  set<int> X[256], Y[256];
  FOR(r, 0, rows) {
    FOR(c, 0, cols) {
      X[grid[r][c]].insert(c);
      Y[grid[r][c]].insert(r);
    }
  }
  FOR(i, 'A', 'Z' + 1) {
    if (!X[i].empty()) {
      FOR(r, *Y[i].begin(), *Y[i].rbegin() + 1)
      FOR(c, *X[i].begin(), *X[i].rbegin() + 1)
      if (grid[r][c] != i) {
        D("false");
        return false;
      }
    }
  }
  D("true");
  return true;
}

bool solve(vector<string> &grid, set<char> &symbols) {
  int r, c;
  for (r = 0; r < rows; ++r)
    for (c = 0; c < cols; ++c)
      if (grid[r][c] == '?')
        goto hell;
hell:;
  D(r);
  D(c);
  if (r == rows)
    return isValid(grid);
  for (char symbol : symbols) {
    D(symbol);
    grid[r][c] = symbol;
    if (solve(grid, symbols))
      return true;
  }
  grid[r][c] = '?';
  return false;
}

int main() {
  cin >> t;

  FOR(caseNr, 1, t + 1) {
    cin >> rows >> cols;
    FOR(i, 'A', 'Z' + 1) {
      X[i].clear();
      Y[i].clear();
    }
    vector<string> grid(rows);
    set<char> symbols;
    FOR(r, 0, rows) {
      cin >> grid[r];
      FOR(c, 0, cols) {
        symbols.insert(grid[r][c]);
        X[grid[r][c]].insert(c);
        Y[grid[r][c]].insert(r);
      }
    }
    FOR(i, 'A', 'Z' + 1) {
      if (!X[i].empty()) {
        FOR(r, *Y[i].begin(), *Y[i].rbegin() + 1)
        FOR(c, *X[i].begin(), *X[i].rbegin() + 1)
        grid[r][c] = i;
      }
    }
    symbols.erase('?');
    solve(grid, symbols);
    cout << "Case #" << caseNr << ":" << endl;
    FOR(r, 0, rows)
    cout << grid[r] << endl;
  }
  return 0;
}
