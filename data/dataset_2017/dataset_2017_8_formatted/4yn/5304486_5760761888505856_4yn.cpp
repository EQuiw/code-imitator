#include <bits/stdc++.h>
using namespace std;

int tc;

int main() {
  cin >> tc;
  for (int t = 1; t <= tc; t++) {
    int r, c;
    cin >> r >> c;
    char cake[30][30];
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        cin >> cake[i][j];
      }
    }
    for (int i = 0; i < r; i++) {
      // sweep left to right
      for (int j = 1; j < c; j++) {
        if (cake[i][j - 1] != '?' && cake[i][j] == '?') {
          cake[i][j] = cake[i][j - 1];
        }
      }
      // sweep right to left
      for (int j = c - 2; j >= 0; j--) {
        if (cake[i][j + 1] != '?' && cake[i][j] == '?') {
          cake[i][j] = cake[i][j + 1];
        }
      }
    }
    for (int i = 1; i < r; i++) {
      // sweep up to down
      if (cake[i - 1][0] != '?' && cake[i][0] == '?') {
        for (int j = 0; j < c; j++) {
          cake[i][j] = cake[i - 1][j];
        }
      }
    }
    for (int i = r - 1; i >= 0; i--) {
      // sweep down to up
      if (cake[i + 1][0] != '?' && cake[i][0] == '?') {
        for (int j = 0; j < c; j++) {
          cake[i][j] = cake[i + 1][j];
        }
      }
    }
    cout << "Case #" << t << ":\n";
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        cout << cake[i][j];
      }
      cout << endl;
    }
  }
}