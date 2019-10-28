#include <algorithm>
#include <float.h>
#include <iostream>
#include <limits.h>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <vector>
using namespace std;

int main() {
  int tests;
  cin >> tests;
  for (int t = 0; t < tests; t++) {
    int R, C;
    cin >> R >> C;
    char board[R][C];
    int firstRow = -1;
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        cin >> board[i][j];
        if ((board[i][j] != '?') && (firstRow == -1)) {
          firstRow = i;
        }
      }
    }
    for (int i = firstRow; i < R; i++) {
      for (int j = 1; j < C; j++) {
        if (board[i][j] == '?') {
          board[i][j] = board[i][j - 1];
        }
      }
      for (int j = C - 2; j >= 0; j--) {
        if (board[i][j] == '?') {
          board[i][j] = board[i][j + 1];
        }
      }
      if (board[i][0] == '?') {
        for (int j = 0; j < C; j++) {
          board[i][j] = board[i - 1][j];
        }
      }
    }
    for (int i = firstRow - 1; i >= 0; i--) {
      for (int j = 0; j < C; j++) {
        board[i][j] = board[i + 1][j];
      }
    }
    cout << "Case #" << (t + 1) << ": " << endl;
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        cout << board[i][j];
      }
      cout << endl;
    }
  }
}
