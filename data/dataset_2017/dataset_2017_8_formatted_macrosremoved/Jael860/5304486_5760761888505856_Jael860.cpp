#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ii> vii;

char grid[55][55];

int R, C;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  ;
  int tt;
  cin >> tt;
  for (int ttt = 1; ttt < tt + 1; ttt++) {
    cout << "Case #" << ttt << ":" << endl;
    cin >> R >> C;
    int row = -1;
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        cin >> grid[i][j];
        if (grid[i][j] != '?')
          row = i;
      }
    }
    assert(row != -1);
    for (int i = 0; i < R; i++) {

      for (int j = 0; j < C; j++) {
        if (grid[i][j] != '?') {
          for (int k = j + 1; k < C; k++) {
            if (grid[i][k] != '?')
              break;
            grid[i][k] = grid[i][j];
          }
        }
      }
    }

    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        if (grid[i][j] != '?') {
          for (int k = j - 1; k >= 0; k--) {
            if (grid[i][k] != '?')
              break;
            grid[i][k] = grid[i][j];
          }
        }
      }
    }
    for (int i = row + 1; i < R; i++) {
      for (int j = 0; j < C; j++) {
        if (grid[i][j] == '?') {
          grid[i][j] = grid[i - 1][j];
        }
      }
    }
    for (int i = row - 1; i >= 0; i--) {
      for (int j = 0; j < C; j++) {
        if (grid[i][j] == '?') {
          grid[i][j] = grid[i + 1][j];
        }
      }
    }
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        assert(grid[i][j] != '?');
        cout << grid[i][j];
      }
      cout << endl;
    }
  }
  return 0;
}
