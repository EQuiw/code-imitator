#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void print(int testNo, const vector<vector<char> >& ans) {
  cout << "Case #" << testNo << ":" << endl;
  for (const auto& r : ans) {
    for (char c : r)
      cout << c;
    cout << endl;
  }
}

int main() {
  int totalTestNo;
  cin >> totalTestNo;
  for (int testNo = 1; testNo <= totalTestNo; ++testNo) {
    int r, c;
    cin >> r >> c;
    vector<vector<char> > board(r, vector<char>(c));
    char t;
    for (int i = 0; i < r; ++i)
      for (int j = 0; j < c; ++j) {
        cin >> t;
        board[i][j] = t;
      }

    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        if (board[i][j] != '?') {
          for (int k = j-1; k >= 0; --k) {
            if (board[i][k] == '?')
              board[i][k] = board[i][j];
            else
              break;
          }
          for (int k = j+1; k < c; ++k) {
            if (board[i][k] == '?')
              board[i][k] = board[i][j];
            else
              break;
          }
        }
      }
    }

    for (int i = 0; i < r; ++i) {
      if (board[i][0] == '?') {
        vector<char> copyRow;
        if (i > 0) copyRow = board[i-1];
        else
          for (int j = i+1; j < r; ++j)
            if (board[j][0] != '?') {
              copyRow = board[j];
              break;
            }

        for (int j = 0; j < c; ++j)
          board[i][j] = copyRow[j];
      }
    }

    print(testNo, board);
  }
}
