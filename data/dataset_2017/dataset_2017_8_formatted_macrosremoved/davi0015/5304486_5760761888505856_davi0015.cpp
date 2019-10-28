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
typedef long long int ll;

int main() {
  int T;
  cin >> T;

  for (int i = 0; i < T; i++) {
    int r, c;
    cin >> r >> c;

    vector<string> grid(r);
    string s;
    vector<pair<int, int>> gridIndex;
    for (int j = 0; j < r; j++) {
      cin >> s;
      grid[j] = s;
      for (int k = 0; k < c; k++) {
        if (s[k] != '?') {
          gridIndex.push_back(make_pair(j, k));
        }
      }
    }

    sort(gridIndex.begin(), gridIndex.end());

    for (int j = 0; j < gridIndex.size(); j++) {
      int done = false;
      int row = gridIndex[j].first;
      int col = gridIndex[j].second;
      int startRow = row, startColumn = col;
      for (int k = 0; k < row + 1; k++) {
        for (int l = 0; l < col + 1; l++) {
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
      for (int k = col + 1; k <= c - 1; k++) {
        if (grid[row][k] != '?') {
          endColumn = k - 1;
          break;
        }
      }
      done = false;
      for (int k = row + 1; k <= r - 1; k++) {
        for (int l = startColumn; l <= endColumn; l++) {
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

      for (int k = startRow; k <= endRow; k++) {
        for (int l = startColumn; l <= endColumn; l++) {
          grid[k][l] = grid[row][col];
        }
      }
    }
    cout << "Case #" << i + 1 << ":" << endl;
    for (int j = 0; j < r; j++) {
      cout << grid[j] << endl;
    }
  }

  return 0;
}
