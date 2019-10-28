#include <iostream>
#include <set>

using namespace std;

int solve(int cc) {
  int r, c;
  cin >> r >> c;
  string str[30];
  for (int i = 0; i < r; i++) {
    cin >> str[i];
  }
  set<char> s;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (str[i][j] != '?' && s.find(str[i][j]) == s.end()) {
        //                    cout<<str[i][j]<<endl;
        int jl = j, jr = j, it = i, ib = i;
        while (jl - 1 >= 0 && str[i][jl - 1] == '?') {
          jl--;
        }
        while (jr + 1 < c && str[i][jr + 1] == '?') {
          jr++;
        }
        while (true) {
          if (it - 1 >= 0) {
            bool check = true;
            for (int k = jl; k <= jr; k++) {
              if (str[it - 1][k] != '?') {
                check = false;
              }
            }
            if (check) {
              it--;
            } else {
              break;
            }
          } else {
            break;
          }
        }
        while (true) {
          if (ib + 1 < r) {
            bool check = true;
            for (int k = jl; k <= jr; k++) {
              if (str[ib + 1][k] != '?') {
                check = false;
              }
            }
            if (check) {
              ib++;
            } else {
              break;
            }
          } else {
            break;
          }
        }
        for (int k = it; k <= ib; k++) {
          for (int l = jl; l <= jr; l++) {
            str[k][l] = str[i][j];
          }
        }
        s.insert(str[i][j]);
      }
    }
  }
  cout << "Case #" << cc << ":" << endl;
  for (int i = 0; i < r; i++) {
    cout << str[i] << endl;
  }
  return 1;
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; i++) {
    solve(i + 1);
  }
  return 0;
}
