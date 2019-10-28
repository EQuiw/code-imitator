#include <bits/stdc++.h>
using namespace std;
typedef pair<long long int, long long int> PI;
typedef pair<long long int, long long int> PI;

inline void solve() {
  cout << endl;
  long long int r, c;
  cin >> r >> c;
  vector<string> board(r);
  for (long long int i = 0; i < ((long long int)(r)); i++)
    cin >> board[i];
  vector<string> res(r);
  for (long long int i = 0; i < ((long long int)(r)); i++)
    res[i] = board[i];
  long long int last_unknown_row = 0;
  for (long long int i = 0; i < ((long long int)(r)); i++) {
    bool empty = true;
    char cc = '?';
    long long int last_unknown_col = 0;
    for (long long int j = 0; j < ((long long int)(c)); j++) {
      if (board[i][j] != '?') {
        empty = false;
        cc = board[i][j];
        for (long long int k = (long long int)(last_unknown_col);
             k < ((long long int)(j)); k++) {
          res[i][k] = cc;
        }
        last_unknown_col = j + 1;
      }
    }
    if (!empty) {
      // 右端をなんとかする
      for (long long int k = (long long int)(last_unknown_col);
           k < ((long long int)(c)); k++) {
        res[i][k] = cc;
      }
      // 今までの未確定行をなんとかする
      for (long long int rr = (long long int)(last_unknown_row);
           rr < ((long long int)(i)); rr++) {
        res[rr] = res[i];
      }
      last_unknown_row = i + 1;
    }
  }
  // 最後の方の未確定行を何とかする
  if (last_unknown_row == 0) {
    throw;
  }
  for (long long int i = (long long int)(last_unknown_row);
       i < ((long long int)(r)); i++) {
    res[i] = res[last_unknown_row - 1];
  }
  for (long long int i = 0; i < ((long long int)(r)); i++)
    cout << res[i] << endl;
}

int main() {
  long long int t;
  cin >> t;
  for (long long int case_num = 0; case_num < ((long long int)(t));
       case_num++) {
    cout << "Case #" << case_num + 1 << ":";
    solve();
  }

  return 0;
}
