#include <bits/stdc++.h>
using namespace std;
string s[50];
int tak[500];
int main() {

  int t, R, C, flag;
  char ch;
  cin >> t;
  for (int tc = 1; tc <= t; tc++) {

    memset(tak, 0, sizeof(tak));
    cin >> R >> C;
    for (int i = 0; i < R; i++)
      cin >> s[i];

    for (int ux = 0; ux < R; ux++) {
      for (int uy = 0; uy < C; uy++) {
        for (int dx = R - 1; dx >= ux; dx--) {
          for (int dy = C - 1; dy >= uy; dy--) {
            flag = 0;
            for (int x = ux; x <= dx; x++) {
              for (int y = uy; y <= dy; y++) {
                if (s[x][y] != '?') {
                  ch = s[x][y];
                  flag++;
                }
              }
            }
            if (flag == 1 && tak[ch] == 0) {
              tak[ch] = 1;
              for (int x = ux; x <= dx; x++) {
                for (int y = uy; y <= dy; y++) {
                  s[x][y] = ch;
                }
              }
            }
          }
        }
      }
    }
    cout << "Case #" << tc << ":";
    ;
    cout << endl;
    for (int x = 0; x < R; x++) {
      cout << s[x] << endl;
    }
  }
}
