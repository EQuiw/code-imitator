#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define forn(I, N) for (int I = 0; I < N; I++)
#define fornd(I, N) for (int I = N - 1; I >= 0; I--)
#define forab(I, A, B) for (int I = A; I <= B; I++)
#define forabd(I, A, B) for (int I = B; I >= A; I--)
#define FOREACH(I, A)                                                          \
  for (__typeof__(A)::iterator I = A.begin(); I < A.end(); I++)
#define pb push_back
#define mp make_pair

typedef long long int ll;

int main() {
  int T;
  cin >> T;

  forn(i, T) {
    int r, c;
    cin >> r >> c;

    vector<string> grid(r);
    string s;
    vector<pair<int, int>> gridIndex;
    forn(j, r) {
      cin >> s;
      grid[j] = s;
      forn(k, c) {
        if (s[k] != '?') {
          gridIndex.pb(mp(j, k));
        }
      }
    }

    sort(gridIndex.begin(), gridIndex.end());

    forn(j, gridIndex.size()) {
      int done = false;
      int row = gridIndex[j].first;
      int col = gridIndex[j].second;
      int startRow = row, startColumn = col;
      forn(k, row + 1) {
        forn(l, col + 1) {
          if (grid[k][l] == '?') {
            startRow = k;
            startColumn = l;
            done = true;
            break;
          }
        }
        if (done) {
          break;
        }
      }

      int endColumn = c - 1;
      int endRow = r - 1;
      forab(k, col + 1, c - 1) {
        if (grid[row][k] != '?') {
          endColumn = k - 1;
          break;
        }
      }
      done = false;
      forab(k, row + 1, r - 1) {
        forab(l, startColumn, endColumn) {
          if (grid[k][l] != '?') {
            endRow = k - 1;
            done = true;
            break;
          }
        }
        if (done) {
          break;
        }
      }
      // cout << startRow << " " << startColumn << " " << endRow << " " <<
      // endColumn << endl;

      forab(k, startRow, endRow) {
        forab(l, startColumn, endColumn) { grid[k][l] = grid[row][col]; }
      }
    }
    cout << "Case #" << i + 1 << ":" << endl;
    forn(j, r) { cout << grid[j] << endl; }
  }

  return 0;
}
