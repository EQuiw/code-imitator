#include <algorithm>
#include <climits>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<double> vd;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<string> vs;
typedef vector<vector<string>> vvs;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef set<int> si;
typedef vector<si> vsi;
using namespace std;

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    int r, c;
    cin >> r >> c;
    vvc grid(r, vc(c));
    vc curLetterAtCol(c);
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        cin >> grid[i][j];
        if (curLetterAtCol[j] == 0 && grid[i][j] != '?') {
          curLetterAtCol[j] = grid[i][j];
        }
      }
    }
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (grid[i][j] == '?') {
          if (curLetterAtCol[j] == 0) {
            if (j > 0) {
              grid[i][j] = grid[i][j - 1];
            }
          } else {
            grid[i][j] = curLetterAtCol[j];
          }
        } else {
          curLetterAtCol[j] = grid[i][j];
        }
      }
    }
    for (int i = 0; i < r; i++) {
      for (int j = c - 1; j >= 0; j--) {
        if (grid[i][j] == '?') {
          if (j < c - 1) {
            grid[i][j] = grid[i][j + 1];
          }
        }
      }
    }
    cout << "Case #" << t << ":\n";
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        cout << grid[i][j];
      }
      cout << '\n';
    }
  }
  return 0;
}
