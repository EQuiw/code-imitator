#include <cstring>
#include <iostream>
using namespace std;

char cake[25][25];

int main() {
  int T;
  cin >> T;
  for (int c = 1; c <= T; ++c) {
    int R, C;
    cin >> R >> C;
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        cin >> cake[i][j];
      }
    }
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        if (cake[i][j] != '?') {
          for (int k = j - 1; k >= 0 && cake[i][k] == '?'; --k) {
            cake[i][k] = cake[i][j];
          }
          for (int k = j + 1; k < C && cake[i][k] == '?'; ++k) {
            cake[i][k] = cake[i][j];
          }
        }
      }
    }
    for (int i = 0; i < R; ++i) {
      if (cake[i][0] != '?') {
        for (int j = i - 1; j >= 0 && cake[j][0] == '?'; --j) {
          for (int k = 0; k < C; ++k) {
            cake[j][k] = cake[i][k];
          }
        }
        for (int j = i + 1; j < R && cake[j][0] == '?'; ++j) {
          for (int k = 0; k < C; ++k) {
            cake[j][k] = cake[i][k];
          }
        }
      }
    }
    cout << "Case #" << c << ":" << endl;
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        cout << cake[i][j];
      }
      cout << endl;
    }
  }
  return 0;
}