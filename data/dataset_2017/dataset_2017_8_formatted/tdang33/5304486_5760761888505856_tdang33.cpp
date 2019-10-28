#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;

void solve(vector<vector<char>> &board, long long r, long long c) {
  int count = 0;
  for (int i1 = 0; i1 < r; i1++) {
    for (int i2 = 0; i2 < c; i2++) {
      if (board[i1][i2] == '?')
        count++;
    }
  }
  while (count > 0) {
    for (int i1 = 0; i1 < r; i1++) {
      for (int i2 = 0; i2 < c; i2++) {
        // cout << board[i1][i2]<<endl;
        if (board[i1][i2] != '?') {
          int a = i1 - 1;
          while (a >= 0 && board[a][i2] == '?') {
            board[a][i2] = board[i1][i2];
            count--;
            a--;
          }
          a = i1 + 1;
          while (a < r && board[a][i2] == '?') {

            board[a][i2] = board[i1][i2];
            count--;
            a++;
          }
        }
      }
    }
    count--;
  }
  for (int i1 = 0; i1 < r; i1++) {
    for (int i2 = 0; i2 < c; i2++) {
      if (board[i1][i2] == '?') {
        if (i2 > 0) {
          for (int k = 0; k < r; k++) {
            board[k][i2] = board[k][i2 - 1];
          }
        } else {
          int l = i2 + 1;
          while (board[i1][l] == '?')
            l++;
          for (int m = l - 1; m >= i2; m--) {
            for (int k = 0; k < r; k++) {
              board[k][m] = board[k][l];
            }
          }
        }
        // for (int k = 0; k < r; k++) {
        //     board[k][i2] = (i2>0?board[k][i2-1] : board[k][i2+1]);
        // }
      }
    }
    // cout <<endl;
  }
  for (int i1 = 0; i1 < r; i1++) {
    for (int i2 = 0; i2 < c; i2++) {
      cout << board[i1][i2];
    }
    cout << endl;
  }
  // cout <<endl;
  // }

  // return "";
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    long long r;
    cin >> r;
    long long c;
    cin >> c;
    vector<vector<char>> board(r, vector<char>(c));
    for (int i1 = 0; i1 < r; i1++) {
      for (int i2 = 0; i2 < c; i2++) {
        cin >> board[i1][i2];
      }
    }
    cout << "Case #" << i + 1 << ": " << endl;
    solve(board, r, c);
  }
  return 0;
}
