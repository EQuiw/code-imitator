#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  int casen;
  cin >> casen;
  for (int casex = 1; casex <= casen; casex++) {
    char cake[50][50];
    bool emptyline[50];
    int firstlinefill = -1;
    int firstcol[50];
    int r, c;
    cin >> r >> c;
    char letter;
    for (int i = 0; i < r; i++) {
      emptyline[i] = true;
      for (int j = 0; j < c; j++) {
        cin >> letter;
        cake[i][j] = letter;
        if (letter != '?') {
          if (firstlinefill == -1)
            firstlinefill = i;
          if (emptyline[i])
            firstcol[i] = j;
          emptyline[i] = false;
        }
      }
    }
    for (int i = firstlinefill; i < r; i++) {
      if (emptyline[i]) {
        for (int j = 0; j < c; j++) {
          cake[i][j] = cake[i - 1][j];
        }
      } else {
        for (int j = 0; j < firstcol[i]; j++)
          cake[i][j] = cake[i][firstcol[i]];
        char lastlet = cake[i][firstcol[i]];
        for (int j = firstcol[i]; j < c; j++) {
          if (cake[i][j] == '?')
            cake[i][j] = lastlet;
          else
            lastlet = cake[i][j];
        }
      }
    }
    for (int i = firstlinefill - 1; i >= 0; i--) {
      for (int j = 0; j < c; j++)
        cake[i][j] = cake[i + 1][j];
    }
    cout << "Case #" << casex << ":" << endl;
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++)
        cout << cake[i][j];
      cout << endl;
    }
  }
  return 0;
}
